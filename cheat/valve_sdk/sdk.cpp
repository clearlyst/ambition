#include "sdk.hpp"

int(__cdecl* RandomInt)(int min, int max);
void(__cdecl* RandomSeed)(uint32_t seed);
float(__cdecl* RandomFloat)(float min, float max);

typedef void* (*InstantiateInterfaceFn)();
class InterfaceReg 
{
public:
    InstantiateInterfaceFn m_CreateFn = 0;
    const char* m_pName;
    InterfaceReg* m_pNext;
};

template <typename T>
T get_iface(const char* file, const char* name, size_t skip = 0)
{
    HMODULE moduleHandle = GetModuleHandle(file);
    if (!moduleHandle) 
    {
        console::get().log(xorstr("weiamware | failed to create handle to %s"), file);
        return 0;
    }

    unsigned int CreateInterface = (unsigned int)GetProcAddress(moduleHandle, xorstr("CreateInterface"));
    if (!CreateInterface) 
    {
        console::get().log(xorstr("weiamware | failed to find CreateInterface in %s\n"), file);
        return 0;
    }

    unsigned int jmp = (CreateInterface + 0x4);
    InterfaceReg* interfaceReg = **(InterfaceReg***)((*(unsigned int*)(jmp + 0x1) + jmp + 0x5) + 0x6);
    for (InterfaceReg* current = interfaceReg; current; current = current->m_pNext) 
    {
        if (strstr(current->m_pName, name) && strlen(current->m_pName) - 3 == strlen(name)) 
        {
            if (skip > 0)
            {
                --skip;
                continue;
            }

            T iface = reinterpret_cast<T>(current->m_CreateFn());
            console::get().log(xorstr("weiamware | found interface %s (%s) at %lx\n"), name, current->m_pName, iface);
            return iface;
        }
    }

    console::get().log(xorstr("weiamware | failed to find interface %s in %s\n"), name, file);

    return 0;
}

#define custom_iface(val, type, ptr, index, add, name) val = **reinterpret_cast<type***>((*reinterpret_cast<uintptr_t**>(ptr))[index] + add); if (val) printf(xorstr("weiamware | custom interface %s found at 0x%p \n"), name, val);

template<class T>
static T* findhudelement(const char* name)
{
    static auto pThis = *reinterpret_cast<DWORD**>(Utils::PatternScan(GetModuleHandleW(L"client.dll"), xorstr("B9 ? ? ? ? E8 ? ? ? ? 8B 5D 08")) + 1);

    static auto find_hud_element = reinterpret_cast<DWORD(__thiscall*)(void*, const char*)>(Utils::PatternScan(GetModuleHandleW(L"client.dll"), xorstr("55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39 77 28")));
    return (T*)find_hud_element(pThis, name);
}

void interfaces::initialize()
{
    g_CHLClient = get_iface<IBaseClientDLL*>(xorstr("client.dll"), xorstr("VClient"));
    g_EntityList = get_iface<IClientEntityList*>(xorstr("client.dll"), xorstr("VClientEntityList"));
    g_Prediction = get_iface<IPrediction*>(xorstr("client.dll"), xorstr("VClientPrediction"));
    g_GameMovement = get_iface<CGameMovement*>(xorstr("client.dll"), xorstr("GameMovement"));
    g_EngineClient = get_iface<IVEngineClient*>(xorstr("engine.dll"), xorstr("VEngineClient"));
    g_MdlInfo = get_iface<IVModelInfoClient*>(xorstr("engine.dll"), xorstr("VModelInfoClient"));
    g_MdlCache = get_iface<IMDLCache*>(xorstr("datacache.dll"), xorstr("MDLCache"));
    g_MdlRender = get_iface<IVModelRender*>(xorstr("engine.dll"), xorstr("VEngineModel"));
    g_RenderView = get_iface<IVRenderView*>(xorstr("engine.dll"), xorstr("VEngineRenderView"));
    g_EngineTrace = get_iface<IEngineTrace*>(xorstr("engine.dll"), xorstr("EngineTraceClient"));
    g_DebugOverlay = get_iface<IVDebugOverlay*>(xorstr("engine.dll"), xorstr("VDebugOverlay"));
    g_GameEvents = get_iface<IGameEventManager2*>(xorstr("engine.dll"), xorstr("GAMEEVENTSMANAGER"), 1);
    g_EngineSound = get_iface<IEngineSound*>(xorstr("engine.dll"), xorstr("IEngineSoundClient"));
    g_MatSystem = get_iface<IMaterialSystem*>(xorstr("materialsystem.dll"), xorstr("VMaterialSystem"));
    g_CVar = get_iface<ICvar*>(xorstr("vstdlib.dll"), xorstr("VEngineCvar"));
    g_FileSystem = get_iface<IBaseFileSystem*>(xorstr("filesystem_stdio.dll"), xorstr("VFileSystem"));
    g_VGuiPanel = get_iface<IPanel*>(xorstr("vgui2.dll"), xorstr("VGUI_Panel"));
    g_VGuiSurface = get_iface<ISurface*>(xorstr("vguimatsurface.dll"), xorstr("VGUI_Surface"));
    g_PhysSurface = get_iface<IPhysicsSurfaceProps*>(xorstr("vphysics.dll"), xorstr("VPhysicsSurfaceProps"));
    g_GameTypes = get_iface<IGameTypes*>(xorstr("matchmaking.dll"), xorstr("VENGINE_GAMETYPES_VERSION"));
    g_StudioRender = get_iface<C_StudioRender*>(xorstr("studiorender.dll"), xorstr("VStudioRender"));
    g_physicsCollision = get_iface<IPhysicsCollision*>(xorstr("vphysics.dll"), xorstr("VPhysicsCollision"));
    g_Console = get_iface<i_console*>(xorstr("vstdlib.dll"), xorstr("VEngineCvar"));
    g_ChatElements = findhudelement<CHudChat>(xorstr("CHudChat"));
    g_Localize = get_iface<i_localize*>(xorstr("localize.dll"), xorstr("Localize_"));
    g_Effects = get_iface<iv_effects*>(xorstr("engine.dll"), xorstr("VEngineEffects"));

    RandomInt = reinterpret_cast<decltype(RandomInt)>(GetProcAddress(GetModuleHandleA(xorstr("vstdlib.dll")), xorstr("RandomInt")));
    RandomSeed = reinterpret_cast<decltype(RandomSeed)>(GetProcAddress(GetModuleHandleA(xorstr("vstdlib.dll")), xorstr("RandomSeed")));
    RandomFloat = reinterpret_cast<decltype(RandomFloat)>(GetProcAddress(GetModuleHandleA(xorstr("vstdlib.dll")), xorstr("RandomFloat")));
    g_MemAlloc = *(C_MemAlloc**)(GetProcAddress(GetModuleHandleA(xorstr("tier0.dll")), xorstr("g_pMemAlloc")));

    custom_iface(g_ClientState, CClientState, g_EngineClient, 12, 0x10, xorstr("client_state"));

    if (g_ClientState)
    {
        console::get().log(xorstr("weiamware | custom interface client state found at 0x%p \n"), g_ClientState);
    }

    custom_iface(g_ClientMode, IClientMode, g_CHLClient, 10, 0x5, xorstr("client_mode"));

    if (g_ClientMode)
    {
        console::get().log(xorstr("weiamware | custom interface client mode at 0x%p \n"), g_ClientMode);
    }

    custom_iface(g_GlobalVars, CGlobalVarsBase, g_CHLClient, 11, 0xA, xorstr("client_mode"));

    if (g_GlobalVars)
    {
        console::get().log(xorstr("weiamware | custom interface globals found at 0x%p \n"), g_GlobalVars);
    }

    g_Input = *(CInput**)(Utils::PatternScan2(xorstr("client.dll"), xorstr("B9 ? ? ? ? F3 0F 11 04 24 FF 50 10")) + 1);

    if (g_Input)
    {
        console::get().log(xorstr("weiamware | custom interface input found at 0x%p \n"), g_Input);
    }

    g_MoveHelper = **(IMoveHelper***)(Utils::PatternScan2(xorstr("client.dll"), xorstr("8B 0D ? ? ? ? 8B 45 ? 51 8B D4 89 02 8B 01")) + 2);

    if (g_MoveHelper)
    {
        console::get().log(xorstr("weiamware | custom interface move helper found at 0x%p \n"), g_MoveHelper);
    }

    g_GlowObjManager = *(glow_manager_t**)(Utils::PatternScan(GetModuleHandleW(L"client.dll"), xorstr("0F 11 05 ? ? ? ? 83 C8 01")) + 3);

    if (g_GlowObjManager)
    {
        console::get().log(xorstr("weiamware | custom interface glow object manager found at 0x%p \n"), g_GlowObjManager);
    }

    g_ViewRender = *(IViewRender**)(Utils::PatternScan2(xorstr("client.dll"), xorstr("A1 ? ? ? ? B9 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? FF 10")) + 1);

    if (g_ViewRender)
    {
        console::get().log(xorstr("weiamware | custom interface view render found at 0x%p \n"), g_ViewRender);
    }

    g_D3DDevice9 = **(IDirect3DDevice9***)(Utils::PatternScan2(xorstr("shaderapidx9.dll"), xorstr("A1 ? ? ? ? 50 8B 08 FF 51 0C")) + 1);

    if (g_D3DDevice9)
    {
        console::get().log(xorstr("weiamware | custom interface d3device9 found at 0x%p \n"), g_D3DDevice9);
    }

    g_WeaponSystem = *(IWeaponSystem**)(Utils::PatternScan2(xorstr("client.dll"), xorstr("8B 35 ? ? ? ? FF 10 0F B7 C0")) + 2);

    if (g_WeaponSystem)
    {
        console::get().log(xorstr("weiamware | custom interface weapon system found at 0x%p \n"), g_WeaponSystem);
    }

    g_ViewRenderBeams = *(IViewRenderBeams**)(Utils::PatternScan2(xorstr("client.dll"), xorstr("A1 ? ? ? ? FF 10 A1 ? ? ? ? B9")) + 1);

    if (g_ViewRenderBeams)
    {
        console::get().log(xorstr("weiamware | custom interface view render beams found at 0x%p \n"), g_ViewRenderBeams);
    }

    if (const HINSTANCE handle = GetModuleHandle(xorstr("vstdlib.dll")))
    {
        g_KeyValuesSystem = reinterpret_cast<void* (__cdecl*)()>(GetProcAddress(handle, "KeyValuesSystem"))();

        if (g_KeyValuesSystem)
        {
            console::get().log(xorstr("weiamware | custom interface key values system found at 0x%p \n"), g_KeyValuesSystem);
        }
    }

    KeyValuesEngine = Utils::PatternScan2(xorstr("engine.dll"), xorstr("85 C0 74 ? 51 6A ? 56 8B C8 E8 ? ? ? ? 8B F0"));

    if (KeyValuesEngine)
    {
        console::get().log(xorstr("weiamware | custom interface key values engine found at 0x%p \n"), KeyValuesEngine);
    }

    KeyValuesClient = Utils::PatternScan2(xorstr("client.dll"), xorstr("85 C0 74 ? 6A ? 6A ? 56 8B C8 E8 ? ? ? ? 8B F0"));

    if (KeyValuesClient)
    {
        console::get().log(xorstr("weiamware | custom interface key values client found at 0x%p \n"), KeyValuesClient);
    }
}

void interfaces::release()
{

}

namespace csgo
{
    player_t* local_player = nullptr;
}