#pragma once

#define NOMINMAX
#include <Windows.h>

#include "Misc/Enums.hpp"
#include "Misc/vfunc.hpp"

#include "Math/VMatrix.hpp"
#include "Math/QAngle.hpp"
#include "Math/Vector.hpp"
#include "Misc/Studio.hpp"

#include "Interfaces/IAppSystem.hpp"
#include "Interfaces/IBaseClientDll.hpp"
#include "Interfaces/IClientEntity.hpp"
#include "Interfaces/IClientEntityList.hpp"
#include "Interfaces/IClientMode.hpp"
#include "Interfaces/IConVar.hpp"
#include "Interfaces/ICvar.hpp"
#include "Interfaces/IEngineTrace.hpp"
#include "Interfaces/IVEngineClient.hpp"
#include "Interfaces/IVDebugOverlay.hpp"
#include "Interfaces/ISurface.hpp"
#include "Interfaces/CInput.hpp"
#include "Interfaces/IVModelInfoClient.hpp"
#include "Interfaces/IVModelRender.hpp"
#include "Interfaces/IRenderView.hpp"
#include "Interfaces/IGameEventmanager.hpp"
#include "Interfaces/IMaterialSystem.hpp"
#include "Interfaces/IMoveHelper.hpp"
#include "Interfaces/IMDLCache.hpp"
#include "Interfaces/IPrediction.hpp"
#include "Interfaces/IPanel.hpp"
#include "Interfaces/IEngineSound.hpp"
#include "Interfaces/IViewRender.hpp"
#include "Interfaces/CClientState.hpp"
#include "Interfaces/IPhysics.hpp"
#include "Interfaces/IInputSystem.hpp"
#include "interfaces/IRefCounted.hpp"
#include "Interfaces/IGameTypes.hpp"
#include "Interfaces/IStudioRender.hpp"
#include "Interfaces/IVModelRenderBeams.hpp"
#include "interfaces/IEffects.hpp"
#include "interfaces/IConsole.hpp"
#include "interfaces/IModelCache.hpp"

#include "Misc/Convar.hpp"
#include "Misc/CUserCmd.hpp"
#include "Misc/glow_outline_effect.hpp"
#include "Misc/datamap.hpp"

#include "Interfaces/IPhysicsCollision.hpp"

#include "netvars.hpp"

#include "../helpers/xor.hpp"
#include "../helpers/Utils.hpp"
#include "../helpers/singleton.hpp"
#include "../console debug/console.hpp"

struct IDirect3DDevice9;

class interfaces : public singleton<interfaces>
{
public:
    void initialize();
    void release();
};

inline IVEngineClient*       g_EngineClient   = nullptr;
inline IBaseClientDLL*       g_CHLClient      = nullptr;
inline IClientEntityList*    g_EntityList     = nullptr;
inline CGlobalVarsBase*      g_GlobalVars     = nullptr;
inline IEngineTrace*         g_EngineTrace    = nullptr;
inline ICvar*                g_CVar           = nullptr;
inline IBaseFileSystem*      g_FileSystem     = nullptr;
inline IPanel*               g_VGuiPanel      = nullptr;
inline IClientMode*          g_ClientMode     = nullptr;
inline IVDebugOverlay*       g_DebugOverlay   = nullptr;
inline ISurface*             g_VGuiSurface    = nullptr;
inline CInput*               g_Input          = nullptr;
inline IVModelInfoClient*    g_MdlInfo        = nullptr;
inline IVModelRender*        g_MdlRender      = nullptr;
inline IMDLCache*           g_MdlCache       = nullptr;
inline IVRenderView*         g_RenderView     = nullptr;
inline IMaterialSystem*      g_MatSystem      = nullptr;
inline IGameEventManager2*   g_GameEvents     = nullptr;
inline IMoveHelper*          g_MoveHelper     = nullptr;
inline IPrediction*          g_Prediction     = nullptr;
inline CGameMovement*        g_GameMovement   = nullptr;
inline IEngineSound*         g_EngineSound    = nullptr;
inline glow_manager_t*       g_GlowObjManager = nullptr;
inline IViewRender*          g_ViewRender     = nullptr;
inline IDirect3DDevice9*     g_D3DDevice9     = nullptr;
inline CClientState*         g_ClientState    = nullptr;
inline IPhysicsSurfaceProps* g_PhysSurface    = nullptr;
inline IWeaponSystem*        g_WeaponSystem   = nullptr;
inline IGameTypes*           g_GameTypes      = nullptr;
inline C_StudioRender*       g_StudioRender   = nullptr;
inline C_MemAlloc*           g_MemAlloc       = nullptr;
inline IViewRenderBeams*     g_ViewRenderBeams = nullptr;
inline IPhysicsCollision*    g_physicsCollision = nullptr;
inline void* g_KeyValuesSystem               = nullptr;
inline std::uint8_t* KeyValuesEngine         = nullptr;
inline std::uint8_t* KeyValuesClient         = nullptr;
inline i_console*    g_Console               = nullptr;
inline CHudChat*     g_ChatElements          = nullptr;
inline i_localize* g_Localize = nullptr;
inline iv_effects* g_Effects = nullptr;

extern void(__cdecl* RandomSeed)(uint32_t seed);
extern int(__cdecl* RandomInt)(int min, int max);
extern float(__cdecl* RandomFloat)(float min, float max);


#include "Misc/EHandle.hpp"

namespace csgo
{
    extern player_t* local_player;
}