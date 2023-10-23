#include "render-imgui.hpp"
#include "../bytes.hpp"

ImFont* titlemenufont;
ImFont* textmenufont;
ImFont* iconmenufont;
ImFont* indicatorsfont;
ImFont* screenmessagefont;
ImFont* firstespfont;
ImFont* secondespfont;
ImFont* weaponiconfont;
ImFont* screenmiscfont;
ImFont* interwebztitlefont;
ImFont* interwebztextfont;

void setupfonts()
{
    auto& io = ImGui::GetIO();
	/*
	ImFontConfig menutextfontconfig;
	menutextfontconfig.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;
	menutextfontconfig.PixelSnapH = true;
	menutextfontconfig.RasterizerMultiply = 2.0f;

    std::string tahoma_font_directory = (std::string)windows_directory + xorstr("\\Fonts\\tahoma.ttf");
    std::string tahoma_bold_font_directory = (std::string)windows_directory + xorstr("\\Fonts\\tahomabd.ttf");
	spectatorlistiwebzfontname = io.Fonts->AddFontFromFileTTF(tahoma_font_directory.c_str(), 13.0f, &menutextfontconfig, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	spectatorlistiwebzfontspectators = io.Fonts->AddFontFromFileTTF(tahoma_bold_font_directory.c_str(), 11.0f, &menutextfontconfig, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	*/

	ImFontConfig titlefontconfig;
	titlefontconfig.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_NoAutoHint | ImGuiFreeTypeBuilderFlags_NoHinting;
	titlefontconfig.PixelSnapH = false;
	titlefontconfig.SizePixels = 16.0f;
	titlefontconfig.RasterizerMultiply = 1.0f;

	ImFontConfig menufontconfig;
	menufontconfig.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_NoAutoHint | ImGuiFreeTypeBuilderFlags_NoHinting;
	menufontconfig.PixelSnapH = false;
	menufontconfig.SizePixels = 16.0f;
	menufontconfig.RasterizerMultiply = 1.0f;

	ImFontConfig screenmessagefontconfig;
	screenmessagefontconfig.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_NoAutoHint | ImGuiFreeTypeBuilderFlags_NoHinting;
	screenmessagefontconfig.PixelSnapH = false;
	screenmessagefontconfig.SizePixels = 10.0f;
	screenmessagefontconfig.RasterizerMultiply = 1.0f;

	ImFontConfig indicatorfontconfig;
	indicatorfontconfig.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_NoAutoHint | ImGuiFreeTypeBuilderFlags_NoHinting;
	indicatorfontconfig.PixelSnapH = false;
	indicatorfontconfig.SizePixels = 29.0f;
	indicatorfontconfig.RasterizerMultiply = 1.0f;

	ImFontConfig firstespfontconfig;
	firstespfontconfig.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;
	firstespfontconfig.PixelSnapH = true;
	firstespfontconfig.SizePixels = 12.0f;
	firstespfontconfig.RasterizerMultiply = 1.0f;

	ImFontConfig secondespfontconfig;
	secondespfontconfig.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;
	secondespfontconfig.PixelSnapH = true;
	secondespfontconfig.SizePixels = 12.0f;
	secondespfontconfig.RasterizerMultiply = 1.0f;

	ImFontConfig screenmiscfontconfig;
	screenmiscfontconfig.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;
	screenmiscfontconfig.PixelSnapH = true;
	screenmiscfontconfig.SizePixels = 12.0f;
	screenmiscfontconfig.RasterizerMultiply = 1.0f;

	ImFontConfig interwebzconfig;
	interwebzconfig.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;
	interwebzconfig.PixelSnapH = true;
	interwebzconfig.RasterizerMultiply = 1.0f;

	char windows_directory[MAX_PATH];
	GetWindowsDirectoryA(windows_directory, MAX_PATH);

	std::string segoe_ui_bold_font_directory = (std::string)windows_directory + xorstr("\\Fonts\\segoeuib.ttf");
	std::string segoe_ui_semibold_font_directory = (std::string)windows_directory + xorstr("\\Fonts\\seguisb.ttf");
	std::string tahoma_font_directory = (std::string)windows_directory + xorstr("\\Fonts\\tahoma.ttf");
	std::string tahoma_bold_font_directory = (std::string)windows_directory + xorstr("\\Fonts\\tahomabd.ttf");
	std::string verdana_font_directory = (std::string)windows_directory + xorstr("\\Fonts\\verdana.ttf");
	std::string verdana_bold_font_directory = (std::string)windows_directory + xorstr("\\Fonts\\verdanab.ttf");
	std::string lucida_font_directory = (std::string)windows_directory + xorstr("\\Fonts\\lucon.ttf");
	std::string weapon_icon_font_directory = (std::string)windows_directory + xorstr("\\Fonts\\astriumwep.ttf");
	std::string menu_icon_font_directory = (std::string)windows_directory + xorstr("\\Fonts\\fontawesome-webfont.ttf");

	static const ImWchar ranges[] = { 0xf000, 0xf3ff, 0 };

	titlemenufont = io.Fonts->AddFontFromFileTTF(segoe_ui_bold_font_directory.c_str(), 16.0f, &titlefontconfig, io.Fonts->GetGlyphRangesCyrillic());
	textmenufont = io.Fonts->AddFontFromFileTTF(segoe_ui_semibold_font_directory.c_str(), 16.0f, &menufontconfig, io.Fonts->GetGlyphRangesCyrillic());
	iconmenufont = io.Fonts->AddFontFromFileTTF(menu_icon_font_directory.c_str(), 16.0f, &menufontconfig, ranges);
	screenmessagefont = io.Fonts->AddFontFromFileTTF(lucida_font_directory.c_str(), 10.0f, &screenmessagefontconfig, io.Fonts->GetGlyphRangesCyrillic());
	indicatorsfont = io.Fonts->AddFontFromFileTTF(verdana_bold_font_directory.c_str(), 29.0f, &indicatorfontconfig, io.Fonts->GetGlyphRangesCyrillic());
	firstespfont = io.Fonts->AddFontFromFileTTF(verdana_font_directory.c_str(), 12.0f, &firstespfontconfig, io.Fonts->GetGlyphRangesCyrillic());
	secondespfont = io.Fonts->AddFontFromFileTTF(verdana_font_directory.c_str(), 12.0f, &secondespfontconfig, io.Fonts->GetGlyphRangesCyrillic());
	screenmiscfont = io.Fonts->AddFontFromFileTTF(tahoma_bold_font_directory.c_str(), 12.0f, &screenmiscfontconfig, io.Fonts->GetGlyphRangesCyrillic());
	weaponiconfont = io.Fonts->AddFontFromFileTTF(weapon_icon_font_directory.c_str(), 12.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	interwebztitlefont = io.Fonts->AddFontFromFileTTF(tahoma_font_directory.c_str(), 13.0f, &interwebzconfig, io.Fonts->GetGlyphRangesCyrillic());
	interwebztextfont = io.Fonts->AddFontFromFileTTF(tahoma_bold_font_directory.c_str(), 11.0f, &interwebzconfig, io.Fonts->GetGlyphRangesCyrillic());

    ImGuiFreeType::BuildFontAtlas(io.Fonts);
}

void imguirender::SetupData()
{
	if (g_D3DDevice9)
	{
		D3DDEVICE_CREATION_PARAMETERS lParams;
		g_D3DDevice9->GetCreationParameters(&lParams);
		m_HWND = lParams.hFocusWindow;
	}

	g_InputSystem->SetupData(m_HWND);

	ImGui::CreateContext();
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    setupfonts();

	ImGui_ImplWin32_Init(m_HWND);
	ImGui_ImplDX9_Init(g_D3DDevice9);
}

void imguirender::SwapDrawData()
{
	std::unique_lock<std::shared_mutex> lock(m_DrawMutex);
	m_DrawListQueue.swap(m_DrawListQueueSafe);
}

void imguirender::ClearDrawData()
{
	if (!m_DrawListQueue.empty())
		m_DrawListQueue.clear();
}

void imguirender::Instance()
{
	std::unique_lock<std::shared_mutex> lock(m_DrawMutex);

	if (m_DrawListQueueSafe.empty())
		return;

	for (auto draw : m_DrawListQueueSafe)
	{
		if (!draw.m_Object.has_value())
			return;

		if (draw.m_Type == DrawObject_NONE) {}

		if (draw.m_Type == DrawObject_LINE)
		{
			const auto& pObject = std::any_cast<LineObject_t>(draw.m_Object);
			ImGui::GetBackgroundDrawList()->AddLine(pObject.m_Min, pObject.m_Max, getU32(pObject.m_Color), pObject.m_fThickness);
		}

		if (draw.m_Type == DrawObject_RECT)
		{
			const auto& pObject = std::any_cast<RectObject_t>(draw.m_Object);
			if (pObject.m_RectType == RectType_Clear)
				ImGui::GetBackgroundDrawList()->AddRect(pObject.m_Min, pObject.m_Max, getU32(pObject.m_Color), pObject.m_fRounding, pObject.m_tCorners, pObject.m_fThickness);
			if (pObject.m_RectType == RectType_Filled)
				ImGui::GetBackgroundDrawList()->AddRectFilled(pObject.m_Min, pObject.m_Max, getU32(pObject.m_Color), pObject.m_fRounding, pObject.m_tCorners);
		}

		if (draw.m_Type == DrawObject_RECTMULTI)
		{
			const auto& pObject = std::any_cast<RectMultiObject_t>(draw.m_Object);
			ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(pObject.m_Min, pObject.m_Max, getU32(pObject.m_Color1), getU32(pObject.m_Color2), getU32(pObject.m_Color3), getU32(pObject.m_Color4));
		}

		if (draw.m_Type == DrawObject_CIRCLE3D)
		{
			const auto& pObject = std::any_cast<Circle3dObject_t>(draw.m_Object);

			static Vector vecPreviousScreenPos = Vector(0, 0, 0);
			static float_t flStep = 3.14159265358979323846f * 2.0f / 72.0f;

			Vector vecScreenPosition = Vector(0, 0, 0);
			if (g_DebugOverlay->screen_position(pObject.Pos, vecScreenPosition))
				return;

			for (float_t flRotation = 0.0f; flRotation <= 3.14159265358979323846f * 2.0f; flRotation += flStep) //-V1034
			{
				Vector vecWorldPosition = Vector(pObject.Radius * cos(flRotation) + pObject.Pos.x, pObject.Radius * sin(flRotation) + pObject.Pos.y, pObject.Pos.z);
				if (g_DebugOverlay->screen_position(vecWorldPosition, vecScreenPosition))
					continue;

				ImGui::GetBackgroundDrawList()->AddLine({ vecPreviousScreenPos.x, vecPreviousScreenPos.y }, { vecScreenPosition.x, vecScreenPosition.y }, getU32(pObject.Color), 1.0f);

				vecPreviousScreenPos = vecScreenPosition;
			}
		}

		if (draw.m_Type == DrawObject_CIRCLE2D)
		{
			const auto& pObject = std::any_cast<Circle3dObject_t>(draw.m_Object);

			Vector vecScreenPosition = Vector(0, 0, 0);
			if (g_DebugOverlay->screen_position(pObject.Pos, vecScreenPosition))
				return;

			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(vecScreenPosition.x, vecScreenPosition.y), pObject.Radius, getU32(pObject.Color), pObject.Points);
		}


		if (draw.m_Type == DrawObject_CIRCLE2DFiled)
		{
			const auto& pObject = std::any_cast<Circle3dObject_t>(draw.m_Object);

			Vector vecScreenPosition = Vector(0, 0, 0);
			if (g_DebugOverlay->screen_position(pObject.Pos, vecScreenPosition))
				return;

			ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(vecScreenPosition.x, vecScreenPosition.y), pObject.Radius, getU32(pObject.Color), pObject.Points);
		}

		if (draw.m_Type == DrawObject_Arc)
		{
			const auto& pObject = std::any_cast<ArcObject_t>(draw.m_Object);

			ImGui::GetBackgroundDrawList()->PathArcTo(pObject.Pos, pObject.Radius, DEG2RAD(pObject.MinAngle), DEG2RAD(pObject.MaxAngle), 32);
			ImGui::GetBackgroundDrawList()->PathStroke(getU32(pObject.Color), false, pObject.Thikness);
		}

		if (draw.m_Type == DrawObject_Triangle)
		{
			const auto& pObject = std::any_cast<TriangleObject_t>(draw.m_Object);

			ImGui::GetBackgroundDrawList()->AddTriangle(ImVec2(pObject.m_Min.x, pObject.m_Min.y), ImVec2(pObject.m_Mun.x, pObject.m_Mun.y), ImVec2(pObject.m_Max.x, pObject.m_Max.y), getU32(pObject.m_Color), pObject.m_fThickness);
		}

		if (draw.m_Type == DrawObject_TriangleFilled)
		{
			const auto& pObject = std::any_cast<TriangleFilledObject_t>(draw.m_Object);

			ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(pObject.m_Min.x, pObject.m_Min.y), ImVec2(pObject.m_Mun.x, pObject.m_Mun.y), ImVec2(pObject.m_Max.x, pObject.m_Max.y), getU32(pObject.m_Color));
		}

		if (draw.m_Type == DrawObject_TEXT)
		{
			auto& pObject = std::any_cast<TextObject_t>(draw.m_Object);

			ImGui::GetBackgroundDrawList()->PushTextureID(pObject.m_Font->ContainerAtlas->TexID);

			if (pObject.Center && !pObject.Right)
			{
				pObject.m_Pos.x -= pObject.m_Font->CalcTextSizeA(pObject.m_fFontSize, FLT_MAX, 0.0f, pObject.m_Text.c_str()).x / 2.0f;
			}

			if (pObject.Right && !pObject.Center)
			{
				pObject.m_Pos.x -= pObject.m_Font->CalcTextSizeA(pObject.m_fFontSize, FLT_MAX, 0.0f, pObject.m_Text.c_str()).x;
			}

            if (!pObject.Outline && pObject.Dropshadow)
            {
                ImGui::GetBackgroundDrawList()->AddText(pObject.m_Font, pObject.m_fFontSize, ImVec2(pObject.m_Pos.x + 1, pObject.m_Pos.y + 1), getU32(color(pObject.m_Color_outline[0], pObject.m_Color_outline[1], pObject.m_Color_outline[2], pObject.m_Color.get_alpha())), pObject.m_Text.c_str());
            }

            if (!pObject.Dropshadow && pObject.Outline)
            {
                ImGui::GetBackgroundDrawList()->AddText(pObject.m_Font, pObject.m_fFontSize, ImVec2(pObject.m_Pos.x + 1, pObject.m_Pos.y + 1), getU32(color(pObject.m_Color_outline[0], pObject.m_Color_outline[1], pObject.m_Color_outline[2], pObject.m_Color.get_alpha())), pObject.m_Text.c_str());
                ImGui::GetBackgroundDrawList()->AddText(pObject.m_Font, pObject.m_fFontSize, ImVec2(pObject.m_Pos.x - 1, pObject.m_Pos.y - 1), getU32(color(pObject.m_Color_outline[0], pObject.m_Color_outline[1], pObject.m_Color_outline[2], pObject.m_Color.get_alpha())), pObject.m_Text.c_str());
				ImGui::GetBackgroundDrawList()->AddText(pObject.m_Font, pObject.m_fFontSize, ImVec2(pObject.m_Pos.x + 1, pObject.m_Pos.y - 1), getU32(color(pObject.m_Color_outline[0], pObject.m_Color_outline[1], pObject.m_Color_outline[2], pObject.m_Color.get_alpha())), pObject.m_Text.c_str());
				ImGui::GetBackgroundDrawList()->AddText(pObject.m_Font, pObject.m_fFontSize, ImVec2(pObject.m_Pos.x - 1, pObject.m_Pos.y + 1), getU32(color(pObject.m_Color_outline[0], pObject.m_Color_outline[1], pObject.m_Color_outline[2], pObject.m_Color.get_alpha())), pObject.m_Text.c_str());
            }


			ImGui::GetBackgroundDrawList()->AddText(pObject.m_Font, pObject.m_fFontSize, pObject.m_Pos, getU32(pObject.m_Color), pObject.m_Text.c_str());

			ImGui::GetBackgroundDrawList()->PopTextureID();
		}
	}
}

void imguirender::AddLine(ImVec2 min, ImVec2 max, color clr, float thickness)
{
	m_DrawListQueue.emplace_back(DrawQueueObject_t(DrawObject_LINE, LineObject_t{ min, max, clr, thickness }));
}

void imguirender::AddRect(ImVec2 min, ImVec2 max, color clr, float thickness, float rounding, ImDrawCornerFlags corners)
{
	m_DrawListQueue.emplace_back(DrawQueueObject_t(DrawObject_RECT, RectObject_t{ min, max, clr, thickness, rounding, corners, RectType_Clear }));
}

void imguirender::AddRectFilled(ImVec2 min, ImVec2 max, color clr, float rounding, ImDrawCornerFlags corners)
{
	m_DrawListQueue.emplace_back(DrawQueueObject_t(DrawObject_RECT, RectObject_t{ min, max, clr, 0, rounding, corners, RectType_Filled }));
}

void imguirender::AddRectFilledMultiColor(ImVec2 min, ImVec2 max, color col, color col2, color col3, color col4)
{
	m_DrawListQueue.emplace_back(DrawQueueObject_t(DrawObject_RECTMULTI, RectMultiObject_t{ min, max, col, col2, col3, col4 }));
}

void imguirender::AddText(ImFont* font, float font_size, ImVec2 pos, std::string text, color clr, color clr_outline, bool outline, bool dropshadow, bool center, bool right)
{
	m_DrawListQueue.emplace_back(DrawQueueObject_t(DrawObject_TEXT, TextObject_t{ font, font_size, pos, text, clr, clr_outline, outline, dropshadow, center, right }));
}

void imguirender::AddCircle3D(Vector position, float points, float radius, color color)
{
	m_DrawListQueue.emplace_back(DrawQueueObject_t(DrawObject_CIRCLE3D, Circle3dObject_t{ position, points, color, radius }));
}

void imguirender::AddCircle2D(Vector position, float points, float radius, color color)
{
	m_DrawListQueue.emplace_back(DrawQueueObject_t(DrawObject_CIRCLE2D, Circle3dObject_t{ position, points, color, radius }));
}

void imguirender::AddCircle2DFilled(Vector position, float points, float radius, color color)
{
	m_DrawListQueue.emplace_back(DrawQueueObject_t(DrawObject_CIRCLE2DFiled, Circle3dObject_t{ position, points, color, radius }));
}

void imguirender::AddArc(ImVec2 position, float radius, float min_angle, float max_angle, color col, float thickness)
{
	m_DrawListQueue.emplace_back(DrawQueueObject_t(DrawObject_Arc, ArcObject_t{ position, radius, min_angle, max_angle, col, thickness }));
}

void imguirender::AddTriangle(ImVec2 position1, ImVec2 position2, ImVec2 position3, color clr, float thickness)
{
	m_DrawListQueue.emplace_back(DrawQueueObject_t(DrawObject_Triangle, TriangleObject_t{ position1, position2, position3, clr, thickness }));
}

void imguirender::AddTriangleFilled(ImVec2 position1, ImVec2 position2, ImVec2 position3, color clr)
{
	m_DrawListQueue.emplace_back(DrawQueueObject_t(DrawObject_TriangleFilled, TriangleFilledObject_t{ position1, position2, position3, clr }));
}