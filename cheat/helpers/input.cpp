#include "input.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void C_InputSystem::SetupData(HWND hWND)
{
	m_hTargetWindow = SetWindowLongA(hWND, GWLP_WNDPROC, (LONG_PTR)(C_InputSystem::WndProc));
}

void C_InputSystem::HandleMessage(UINT msg, WPARAM wParam)
{
	switch (msg)
	{
	case WM_XBUTTONDOWN:
	{
		DWORD dwParam = wParam;
		if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
			dwParam = VK_XBUTTON1;
		else if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2)
			dwParam = VK_XBUTTON2;

		m_HeldKeys[dwParam] = true;
		m_ToggledKeys[dwParam] = !m_ToggledKeys[dwParam];
		break;
	}

	case WM_XBUTTONUP:
	{
		DWORD dwParam = wParam;
		if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
			dwParam = VK_XBUTTON1;
		else if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2)
			dwParam = VK_XBUTTON2;

		m_HeldKeys[dwParam] = false;
		break;
	}

	case WM_MBUTTONDOWN:
	{
		m_ToggledKeys[VK_MBUTTON] = !m_ToggledKeys[VK_MBUTTON];
		m_HeldKeys[VK_MBUTTON] = true;
		break;
	}

	case WM_MBUTTONUP:
	{
		m_HeldKeys[VK_MBUTTON] = false;
		break;
	}

	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	{
		m_HeldKeys[wParam] = false;
		m_ToggledKeys[wParam] = !m_ToggledKeys[wParam];
		break;
	}

	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		m_HeldKeys[wParam] = false;
		break;
	};
	}
}

LRESULT WINAPI C_InputSystem::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	g_InputSystem->HandleMessage(msg, wParam);

	menu::get().SetVisible(g_InputSystem->IsToggled(VK_INSERT));

	// is any keys
	bool bPressedMenuKeys = false;
	if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP || msg == WM_LBUTTONUP || msg == WM_MOUSEMOVE || msg == WM_MOUSEWHEEL)
		bPressedMenuKeys = true;

	bool bIsMenuVisible = menu::get().IsVisible();
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		if (bIsMenuVisible)
			return true;

	if (bIsMenuVisible)
		if (bPressedMenuKeys)
			return false;

	return CallWindowProc((WNDPROC)(g_InputSystem->m_hTargetWindow), hWnd, msg, wParam, lParam);
}