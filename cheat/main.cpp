#include <ctime>
#include <mutex>
#include <string>
#include <chrono>
#include <optional>
#include <Lmcons.h>
#include <windows.h>

#include "menu.hpp"
#include "discord.hpp"
#include "variables.hpp"
#include "hooks/hooks.hpp"
#include "helpers/input.hpp"
#include "console debug/console.hpp"
#include "renders/render-surface.hpp"
#include "features/config system/config.hpp"
#include "features/notifications/notifications.hpp"

void initialize(HINSTANCE hInstance)
{
    while (!GetModuleHandleA(xorstr("serverbrowser.dll")))
    {
        Sleep(200);
    }

#ifdef _DEBUG
   console::get().initialize(xorstr("weiamware | console"));

   console::get().log(xorstr("weiamware | welcome\n"));
   console::get().log(xorstr("weiamware | interfaces initializing\n"));
   interfaces::get().initialize();
   console::get().log(xorstr("weiamware | interfaces initialized\n"));

   console::get().log(xorstr("weiamware | discord rpc initializing\n"));
   discordrpc::get().initialize();
   console::get().log(xorstr("weiamware | discord rpc initialized\n"));

   console::get().log(xorstr("weiamware | imgui render initializing\n"));
   imguirender::get().SetupData();
   console::get().log(xorstr("weiamware | imgui render initialized\n"));

   console::get().log(xorstr("weiamware | hook system initializing\n"));
   hooksystem::get().initialize();
   console::get().log(xorstr("weiamware | hook system initialized\n"));

   console::get().log(xorstr("weiamware | config system initializing\n"));
   configsystem::get().create_directory();
   console::get().log(xorstr("weiamware | config system initialized\n"));

   console::get().log(xorstr("weiamware | surface render initializing\n"));
   surfacerender::get().initialize();
   console::get().log(xorstr("weiamware | surface render initialized\n"));

   console::get().log(xorstr("weiamware | initialized\n"));
#endif

   interfaces::get().initialize();
   discordrpc::get().initialize();
   imguirender::get().SetupData();
   hooksystem::get().initialize();
   configsystem::get().create_directory();
   surfacerender::get().initialize();

   g_EngineClient->ClientCmd(xorstr("clear"));
   notify::get().run(xorstr("completely hack initialized | csgo build: ") + std::to_string(g_EngineClient->GetEngineBuildNumber()), true, false, true);
}

void release()
{
    hooksystem::get().release();
    menu::get().release();
    discordrpc::get().release();

    #ifdef _DEBUG
        console::get().release();
    #endif
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwReasonForCall, LPVOID lpReserved)
{
    if (dwReasonForCall == DLL_PROCESS_ATTACH)
    {
        initialize(hModule);
    }

    return TRUE;
}