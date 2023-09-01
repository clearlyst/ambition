#pragma once

#include "../menu.hpp"
#include "../helpers/xor.hpp"
#include "../helpers/fnv.hpp"
#include "../helpers/Utils.hpp"
#include "../features/esp/esp.hpp"
#include "../helpers/singleton.hpp"
#include "../features/misc/misc.hpp"
#include "../features/glow/glow.hpp"
#include "../features/chams/chams.hpp"
#include "../console debug/console.hpp"
#include "../features/aimbot/aimbot.hpp"
#include "../features/movement/movement.hpp"
#include "../features/backtrack/backtrack.hpp"
#include "../features/config system/config.hpp"
#include "../features/triggerbot/triggerbot.hpp"
#include "../features/indicators/indicators.hpp"
#include "../features/notifications/notifications.hpp"
#include "../features/engine prediction/prediction.hpp"

#include "minhook/minhook.h"


class hooksystem : public singleton<hooksystem>
{
public:
	inline unsigned int get_virtual(void* _class, unsigned int index) 
	{ 
		return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); 
	}

	bool initialize();
	void release();
};


namespace end_scene
{
	using fn = HRESULT(__stdcall*)(IDirect3DDevice9*);
	HRESULT __stdcall run(IDirect3DDevice9* device);
}

namespace reset
{
	using fn = HRESULT(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
	HRESULT __stdcall run(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params);
}

namespace check_file_crcserver 
{
	using fn = void(__thiscall*)(void*, void*);
	void __fastcall run(void*, void*);
}

namespace loose_file_allowed
{
	using fn = bool(__thiscall*)(void*, void*);
	bool __fastcall run(void*, void*);
}

namespace alloc_key_values 
{
	using fn = void* (__thiscall*)(void*, const std::int32_t);
	void* __stdcall run(const std::int32_t size);
}

namespace modify_eye_position 
{
	using fn = void(__fastcall*)(LPVOID, uint32_t, Vector&);
	void __fastcall run(LPVOID ecx, uint32_t, Vector& inputeyeposition);
}

namespace send_net_message
{
	using fn = bool(__fastcall*)(INetChannel*, void*, INetMessage&, bool, bool);
	bool __fastcall run(INetChannel* this_ptr, void* edx, INetMessage& msg, bool force_reliable, bool voice);
}

namespace retaddr
{
	using fn = bool(__fastcall*)(void*, void*, const char*);
	bool __fastcall run(void* ecx, void* rcx, const char* m_modulename);
}

namespace paint_traverse
{
	using fn = void(__thiscall*)(IPanel*, unsigned int, bool, bool);
	void __stdcall run(vgui::VPANEL panel, bool force_repaint, bool allow_force);
}

namespace lock_cursor 
{
	using fn = void(__fastcall*)(LPVOID);
	void __fastcall run(LPVOID pEcx, uint32_t);
}

namespace create_move
{
	using fn = bool(__stdcall*)(float, CUserCmd*);
	bool __stdcall run(float input_sample_frametime, CUserCmd* cmd);
}

namespace emit_sound 
{
	using fn = void(__thiscall*)(void*, void*, int, int, const char*, unsigned int, const char*, float, int, float, int, int, const Vector*, const Vector*, void*, bool, float, int, int);
	void __stdcall run(void* filter, int index, int ichannel, const char* soundentry, unsigned int soundhash, const char* sample, float volume, int seed, float flattenuation, int iflags, int ipitch, const Vector* origin, const Vector* direction, void* utlvecorigins, bool updatepositions, float soundtime, int speakerentity, int unk);
}

namespace do_post_screen_effects 
{
	using fn = bool(__thiscall*)(void*, CViewSetup*);
	bool __stdcall run(CViewSetup* setup);
}

namespace draw_model_execute 
{
	using fn = void(__thiscall*)(void*, IMatRenderContext*, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4_t*);
	void __fastcall run(void* ecx, void* edx, IMatRenderContext* context, const DrawModelState_t& state, const ModelRenderInfo_t& render_info, matrix3x4_t* matrix);
}
inline draw_model_execute::fn draw_model_execute_original = nullptr;

namespace frame_stage_notify
{
	using fn = void(__thiscall*)(void*, int);
	void __stdcall run(int stage);
}

namespace override_mouse_input
{
	using fn = void(__fastcall*)(void*, int, float*, float*);
	void __fastcall run(void* thisptr, int edx, float* x, float* y);
}

namespace is_connected
{
	using fn = bool(__thiscall*)(IVEngineClient*);
	bool __stdcall run();
}