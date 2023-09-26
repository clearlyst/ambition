#include "hooks.hpp"

end_scene::fn end_scene_original = nullptr;
reset::fn reset_original = nullptr;
check_file_crcserver::fn check_file_crcserver_original = nullptr;
loose_file_allowed::fn loose_file_allowed_original = nullptr;
alloc_key_values::fn alloc_key_values_original = nullptr;
modify_eye_position::fn modify_eye_position_original = nullptr;
send_net_message::fn send_net_message_original = nullptr;
retaddr::fn retaddr_original = nullptr;
paint_traverse::fn paint_traverse_original = nullptr;
create_move::fn create_move_original = nullptr;
emit_sound::fn emit_sound_original = nullptr;
do_post_screen_effects::fn do_post_screen_effects_original = nullptr;
frame_stage_notify::fn frame_stage_notify_original = nullptr;
lock_cursor::fn lock_cursor_original = nullptr;
override_mouse_input::fn override_mouse_input_original = nullptr;
is_connected::fn is_connected_original = nullptr;

bool hooksystem::initialize()
{
	const auto end_scene_target = reinterpret_cast<void*>(get_virtual(g_D3DDevice9, 42));
	const auto reset_target = reinterpret_cast<void*>(get_virtual(g_D3DDevice9, 16));
	auto check_file_crcserver_target = reinterpret_cast<void*>(Utils::PatternScan2(xorstr("engine.dll"), xorstr("55 8B EC 81 EC ? ? ? ? 53 8B D9 89 5D F8 80")));
	const auto loose_file_allowed_target = reinterpret_cast<void*>(get_virtual(g_FileSystem, 128));
	const auto alloc_key_values_target = reinterpret_cast<void*>(get_virtual(g_KeyValuesSystem, 2));
	auto modify_eye_position_target = reinterpret_cast<void*>(Utils::PatternScan2(xorstr("client.dll"), xorstr("55 8B EC 83 E4 F8 83 EC 70 56 57 8B F9 89 7C 24 14 83 7F 60")));
	auto send_net_message_target = Utils::PatternScan2(xorstr("engine.dll"), xorstr("55 8B EC 83 EC 08 56 8B F1 8B 4D 04 E8"));
	auto result = reinterpret_cast<void*>(Utils::PatternScan2(xorstr("client.dll"), xorstr("55 8B EC 56 8B F1 33 C0 57 8B 7D 08 8B 8E ? ? ? ? 85 C9 7E 16 3B 3C 86")));
	auto result1 = reinterpret_cast<void*>(Utils::PatternScan2(xorstr("engine.dll"), xorstr("55 8B EC 56 8B F1 33 C0 57 8B 7D 08 8B 8E ? ? ? ? 85 C9 7E 16 3B 3C 86")));
	auto result2 = reinterpret_cast<void*>(Utils::PatternScan2(xorstr("studiorender.dll"), xorstr("55 8B EC 56 8B F1 33 C0 57 8B 7D 08 8B 8E ? ? ? ? 85 C9 7E 16 3B 3C 86")));
	auto result3 = reinterpret_cast<void*>(Utils::PatternScan2(xorstr("materialsystem.dll"), xorstr("55 8B EC 56 8B F1 33 C0 57 8B 7D 08 8B 8E ? ? ? ? 85 C9 7E 16 3B 3C 86")));
	const auto paint_traverse_target = reinterpret_cast<void*>(get_virtual(g_VGuiPanel, 41));
	const auto create_move_target = reinterpret_cast<void*>(get_virtual(g_ClientMode, 24));
	const auto is_connected_target = reinterpret_cast<void*>(get_virtual(g_EngineClient, 27));
	const auto emit_sound_target = reinterpret_cast<void*>(get_virtual(g_EngineSound, 5));
	const auto do_post_screen_effects_target = reinterpret_cast<void*>(get_virtual(g_ClientMode, 44));
	const auto draw_model_execute_target = reinterpret_cast<void*>(get_virtual(g_MdlRender, 21));
	const auto frame_stage_notify_target = reinterpret_cast<void*>(get_virtual(g_CHLClient, 37));
	const auto lock_cursor_target = reinterpret_cast<void*>(get_virtual(g_VGuiSurface, 67));
	const auto override_mouse_input_target = reinterpret_cast<void*>(get_virtual(g_ClientMode, 23));

	if (MH_Initialize() != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize minhook"));
	}

	if (MH_CreateHook(end_scene_target, &end_scene::run, reinterpret_cast<void**>(&end_scene_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize end scene hook"));
	}

	if (MH_CreateHook(reset_target, &reset::run, reinterpret_cast<void**>(&reset_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize reset hook"));
	}
	
	if (MH_CreateHook(lock_cursor_target, &lock_cursor::run, reinterpret_cast<void**>(&lock_cursor_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize lock cursor hook"));
	}

	if (MH_CreateHook(check_file_crcserver_target, &check_file_crcserver::run, reinterpret_cast<void**>(&check_file_crcserver_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize check_file_crcserver hook"));
	}
	
	if (MH_CreateHook(loose_file_allowed_target, &loose_file_allowed::run, reinterpret_cast<void**>(&loose_file_allowed_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize loose_file_allowed hook"));
	}
	
	if (MH_CreateHook(alloc_key_values_target, &alloc_key_values::run, reinterpret_cast<void**>(&alloc_key_values_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize alloc_key_values hook"));
	}

	if (MH_CreateHook(result, &retaddr::run, reinterpret_cast<void**>(&retaddr_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to bypass retaddr_client hook"));
	}

	if (MH_CreateHook(result1, &retaddr::run, reinterpret_cast<void**>(&retaddr_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to bypass retaddr_engine hook"));
	}

	if (MH_CreateHook(result2, &retaddr::run, reinterpret_cast<void**>(&retaddr_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to bypass retaddr_studiorender hook"));
	}

	if (MH_CreateHook(result3, &retaddr::run, reinterpret_cast<void**>(&retaddr_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to bypass retaddr_materialsystem hook"));
	}

	if (MH_CreateHook(modify_eye_position_target, &modify_eye_position::run, reinterpret_cast<void**>(&modify_eye_position_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize modify_eye_position hook"));
	}

	if (MH_CreateHook(send_net_message_target, &send_net_message::run, reinterpret_cast<void**>(&send_net_message_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize send_net_message hook"));
	}

	if (MH_CreateHook(paint_traverse_target, &paint_traverse::run, reinterpret_cast<void**>(&paint_traverse_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize paint_traverse hook"));
	}

	if (MH_CreateHook(create_move_target, &create_move::run, reinterpret_cast<void**>(&create_move_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize create_move hook"));
	}

	if (MH_CreateHook(emit_sound_target, &emit_sound::run, reinterpret_cast<void**>(&emit_sound_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize emit_sound_target hook"));
	}

	if (MH_CreateHook(do_post_screen_effects_target, &do_post_screen_effects::run, reinterpret_cast<void**>(&do_post_screen_effects_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize do_post_screen_effects hook"));
	}

	if (MH_CreateHook(draw_model_execute_target, &draw_model_execute::run, reinterpret_cast<void**>(&draw_model_execute_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize draw_model_execute_target hook"));
	}

	if (MH_CreateHook(frame_stage_notify_target, &frame_stage_notify::run, reinterpret_cast<void**>(&frame_stage_notify_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize frame_stage_notify_target hook"));
	}

	if (MH_CreateHook(override_mouse_input_target, &override_mouse_input::run, reinterpret_cast<void**>(&override_mouse_input_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize override_mouse_input hook"));
	}

	if (MH_CreateHook(is_connected_target, &is_connected::run, reinterpret_cast<void**>(&is_connected_original)) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to initialize is_connected hook"));
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
	{
		throw std::runtime_error(xorstr("failed to enable hooks"));
	}

	return true;
}

void hooksystem::release()
{
	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);
}

void __fastcall check_file_crcserver::run(void*, void*)
{
	return;
}

bool __fastcall loose_file_allowed::run(void*, void*)
{
	return true;
}

void* __stdcall alloc_key_values::run(const std::int32_t size)
{
	if (const std::uint32_t address = reinterpret_cast<std::uint32_t>(_ReturnAddress()); address == reinterpret_cast<std::uint32_t>(KeyValuesEngine) || address == reinterpret_cast<std::uint32_t>(KeyValuesClient))
	{
		return nullptr;
	}

	return alloc_key_values_original(g_KeyValuesSystem, size);
}

bool __fastcall retaddr::run(void* ecx, void* rcx, const char* m_modulename)
{
	return true;
}

void __fastcall modify_eye_position::run(LPVOID ecx, uint32_t, Vector& inputeyeposition) 
{
	return;
}

bool __fastcall send_net_message::run(INetChannel* this_ptr, void* edx, INetMessage& msg, bool force_reliable, bool voice)
{
	if (msg.GetType() == 14)
	{
		return false;
	}

	if (msg.GetGroup() == 9)
	{
		voice = true;
	}

	return send_net_message_original(this_ptr, edx, msg, force_reliable, voice);
}

HRESULT WINAPI end_scene::run(IDirect3DDevice9* pDevice)
{
	IDirect3DVertexDeclaration9* pVertDec;
	if (pDevice->GetVertexDeclaration(&pVertDec))
		return end_scene_original(pDevice);

	IDirect3DVertexShader9* pVertShader;
	if (pDevice->GetVertexShader(&pVertShader))
		return end_scene_original(pDevice);

	DWORD dwOldD3DRSColorWriteEnable = NULL;
	DWORD dwColorWrite = 0;
	DWORD dwSRGBWrite = 0;

	pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &dwColorWrite);
	pDevice->GetRenderState(D3DRS_SRGBWRITEENABLE, &dwSRGBWrite);

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOldD3DRSColorWriteEnable);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(NULL, D3DSAMP_SRGBTEXTURE, NULL);


	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	imguirender::get().Instance();
	menu::get().render();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dwColorWrite);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, dwSRGBWrite);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dwOldD3DRSColorWriteEnable);
	pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, true);

	pDevice->SetVertexShader(pVertShader);
	pDevice->SetVertexDeclaration(pVertDec);

	// return original end scene
	return end_scene_original(pDevice);
}

HRESULT WINAPI reset::run(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pDeviceParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	HRESULT lResult = reset_original(pDevice, pDeviceParameters);

	if (SUCCEEDED(lResult))
		ImGui_ImplDX9_CreateDeviceObjects();

	return lResult;
}

void __fastcall lock_cursor::run(LPVOID pEcx, uint32_t)
{
	if (menu::get().IsVisible())
	{
		return g_VGuiSurface->unlock_cursor();
	}

	return lock_cursor_original(pEcx);
}

void __stdcall paint_traverse::run(vgui::VPANEL panel, bool force_repaint, bool allow_force)
{
	const auto panel_name = fnv::hash(g_VGuiPanel->get_panel_name(panel));

	switch (panel_name)
	{
	    case fnv::hash("MatSystemTopPanel"):
	    
	    	break;
	    case fnv::hash("FocusOverlayPanel"):
	    	imguirender::get().ClearDrawData();
	    
	    	notify::get().draw();
	    	indicators::get().velocity();
	    	indicators::get().stamina();
	    	indicators::get().velograph_draw();
	    	indicators::get().staminagraph_draw();
	    	indicators::get().addindicators();
	    	esp::get().run();
	    	misc::get().spectatorlist();
	    	misc::get().watermark();
	    	misc::get().snipercrosshair();
	    	misc::get().spotifymusic();
	    
	    	imguirender::get().SwapDrawData();
	    	break;
	}


	paint_traverse_original(g_VGuiPanel, panel, force_repaint, allow_force);
}

bool __stdcall create_move::run(float input_sample_frametime, CUserCmd* cmd)
{
	create_move_original(input_sample_frametime, cmd);

	if (!cmd || !cmd->command_number)
	{
		return true;
	}

	csgo::local_player = static_cast<player_t*>(g_EntityList->GetClientEntity(g_EngineClient->GetLocalPlayer()));

	misc::get().rankreavel(cmd);
	misc::get().usespammer(cmd);
	misc::get().forcecrosshair();
	misc::get().recoilcrosshair();

	movement::get().resetdetection();
	movement::get().pre_prediction(cmd);
	movement::get().bunnyhop(cmd);
	movement::get().infinityduck(cmd);
	indicators::get().velocitygraph_gather_data();
	indicators::get().staminagraph_gather_data();

	engine_prediction::get().init();
	engine_prediction::get().repredict(cmd);
	{
		aimbot::get().run(cmd);
		backtrack::get().run(cmd);
		triggerbot::get().run(cmd);
		movement::get().autoalign(cmd);
	}
	engine_prediction::get().restore();

	movement::get().edgejump(cmd);
	movement::get().longjump(cmd);
	movement::get().ladderedgejump(cmd);
	movement::get().minijump(cmd);
	movement::get().jumpbug(cmd);
	movement::get().autoduck(cmd);
	movement::get().staminahop(cmd);
	movement::get().autopixelsurf(cmd);
	movement::get().blockbot(cmd);

	auto backup_viewangles = cmd->viewangles;
	movement::get().autoedgebug(cmd);
	math::start_movement_fix(cmd);
	cmd->viewangles = backup_viewangles;
	math::end_movement_fix(cmd);
	
	cmd->viewangles.clamp();
	
	movement::get().edgebug_old_viewangles = cmd->viewangles;

	return false;
}

void __stdcall emit_sound::run(void* filter, int index, int ichannel, const char* soundentry, unsigned int soundhash, const char* sample, float flvolume, int seed, float flattenuation, int iflags, int ipitch, const Vector* origin, const Vector* direction, void* utlvecorigins, bool updatepositions, float soundtime, int speakerentity, int unk)
{
	if (!strcmp(soundentry, xorstr("UIPanorama.popup_accept_match_beep")) && variables::config::misc::autoaccept)
	{
		static auto accept = reinterpret_cast<bool(__stdcall*)(const char*)>(Utils::PatternScan2(xorstr("client.dll"), xorstr("55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));

		if (accept)
		{
			accept(xorstr(""));
		}
	}

	if (!engine_prediction::get().bInPrediction)
	{
		return emit_sound_original(g_EngineSound, filter, index, ichannel, soundentry, soundhash, sample, flvolume, seed, flattenuation, iflags, ipitch, origin, direction, utlvecorigins, updatepositions, soundtime, speakerentity, unk);
	}
}

bool __stdcall do_post_screen_effects::run(CViewSetup* setup)
{
	glow::get().run();

	return do_post_screen_effects_original(g_ClientMode, setup);
}

void __fastcall draw_model_execute::run(void* ecx, void* edx, IMatRenderContext* context, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* matrix)
{
	static auto chams_init = (chams::get().initialize(), false);

	bool forced_mat = !g_MdlRender->IsForcedMaterialOverride();

	if (forced_mat)
		chams::get().run(context, state, pInfo, matrix);


	draw_model_execute_original(ecx, context, state, pInfo, matrix);

	if (forced_mat)
		g_MdlRender->ForcedMaterialOverride(nullptr);
}

void __stdcall frame_stage_notify::run(int stage)
{
	if (stage == FRAME_RENDER_START)
	{
		misc::get().regionchanger();
	}

	misc::get().changeviewmodeloffsets();
	misc::get().changeviewmodelfov();
	misc::get().changeweaponswayscale();
	misc::get().removeflash();
	misc::get().removesmoke();
	misc::get().removefire();

	return frame_stage_notify_original(g_CHLClient, stage);
}

void __fastcall override_mouse_input::run(void* thisptr, int edx, float* x, float* y)
{
	movement::get().autoedgebug_lock(*x, *y);
	movement::get().mousespeedlimiter(*x, *y);

	override_mouse_input_original(thisptr, edx, x, y);
}

bool __stdcall is_connected::run() 
{
	static void* force_inventory_open = Utils::PatternScan2(xorstr("client.dll"), xorstr("84 C0 75 05 B0 01 5F")) - 2;

	if (variables::config::misc::unlockinventory && _ReturnAddress() == force_inventory_open)
	{
		return false;
	}

	return is_connected_original(g_EngineClient);
}
