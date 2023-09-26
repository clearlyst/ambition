#include "backtrack.hpp"

void backtrack::run(CUserCmd* cmd)
{
	const auto current_settings = aimbot::get().get_current_settings();

	if (!current_settings.backtrack)
	{
		data.clear();

		return;
	}

	if (!g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
	{
		data.clear();

		return;
	}

	if (!csgo::local_player || !csgo::local_player->is_alive() || csgo::local_player->is_defusing())
	{
		data.clear();

		return;
	}

	if (menu::get().IsVisible())
	{
		data.clear();

		return;
	}

	auto weapon = csgo::local_player->active_weapon();

	if (!weapon || weapon->clip1_count() == 0)
	{
		data.clear();

		return;
	}

	auto weapon_data = weapon->get_weapon_data();

	if (!weapon_data)
	{
		data.clear();

		return;
	}

	static ConVar* sv_max_unlag = g_CVar->FindVar("sv_maxunlag");
	static ConVar* sv_min_update_rate = g_CVar->FindVar("sv_minupdaterate");
	static ConVar* sv_max_update_rate = g_CVar->FindVar("sv_maxupdaterate");

	static ConVar* sv_client_min_interp_ratio = g_CVar->FindVar("sv_client_min_interp_ratio");
	static ConVar* sv_client_max_interp_ratio = g_CVar->FindVar("sv_client_max_interp_ratio");

	static ConVar* cl_interp_ratio = g_CVar->FindVar("cl_interp_ratio");
	static ConVar* cl_interp = g_CVar->FindVar("cl_interp");
	static ConVar* cl_updaterate = g_CVar->FindVar("cl_updaterate");

	float float_max_unlag = sv_max_unlag->GetFloat();

	float float_update_rate = cl_updaterate->GetFloat();

	float float_min_update_rate = sv_min_update_rate->GetFloat();
	float float_max_update_rate = sv_max_update_rate->GetFloat();

	float float_min_interp = sv_client_min_interp_ratio->GetFloat();
	float float_max_interp = sv_client_max_interp_ratio->GetFloat();

	float float_lerp_amount = cl_interp->GetFloat();
	float float_lerp_ratio = cl_interp_ratio->GetFloat();

	float_lerp_ratio = std::clamp(float_lerp_ratio, float_min_interp, float_max_interp);

	if (float_lerp_ratio == 0.0f)
	{
		float_lerp_ratio = 1.0f;
	}

	float update_rate = std::clamp(float_update_rate, float_min_update_rate, float_max_update_rate);

	latency = g_EngineClient->GetNetChannelInfo()->GetLatency(FLOW_OUTGOING) + g_EngineClient->GetNetChannelInfo()->GetLatency(FLOW_INCOMING);

	lerp_time = std::fmaxf(float_lerp_amount, float_lerp_ratio / update_rate);

	correct_time += latency;
	correct_time += lerp_time;
	correct_time = std::clamp(correct_time, 0.f, float_max_unlag);

	for (auto i = 1; i < g_GlobalVars->maxClients; i++)
	{
		player_t* entity = player_t::GetPlayerByIndex(i);

		if (!entity || !entity->is_alive() || !entity->is_player() || entity == csgo::local_player || entity->has_gun_game_immunity() || entity->IsDormant())
		{
			if (data.count(i) > 0)
			{
				data.erase(i);
			}

			continue;
		}

		if (entity->team() == csgo::local_player->team() && !current_settings.teammates)
		{
			if (data.count(i) > 0)
			{
				data.erase(i);
			}

			continue;
		}

		if (!(entity->flags() & FL_ONGROUND) && current_settings.enemyinair)
		{
			if (data.count(i) > 0)
			{
				data.erase(i);
			}

			continue;
		}

		if (!(csgo::local_player->flags() & FL_ONGROUND) && current_settings.selfinair)
		{
			if (data.count(i) > 0)
			{
				data.erase(i);
			}

			continue;
		}

		if (csgo::local_player->flash_duration() > 1.f && current_settings.flashcheck)
		{
			if (data.count(i) > 0)
			{
				data.erase(i);
			}

			continue;
		}

		auto& cur_data = data[i];

		if (!cur_data.empty()) 
		{
			auto& front = cur_data.front();

			if (front.sim_time == entity->simulation_time())
			{
				continue;
			}

			while (!cur_data.empty())
			{
				auto& back = cur_data.back();

				delta_time = correct_time - (g_GlobalVars->curtime - back.sim_time);

				if (std::fabsf(delta_time) <= 0.2f)
				{
					break;
				}

				cur_data.pop_back();
			}
		}

		auto model = entity->GetModel();

		if (!model)
		{
			continue;
		}

		auto hdr = g_MdlInfo->GetStudiomodel(model);

		if (!hdr)
		{
			continue;
		}

		auto hitbox_set = hdr->GetHitboxSet(entity->hitbox_set());
		auto hitbox_head = hitbox_set->GetHitbox(HITBOX_HEAD);
		auto hitbox_center = (hitbox_head->bbmin + hitbox_head->bbmax) * 0.5f;

		backtrack_data record;
		record.sim_time = entity->simulation_time();

		*(Vector*)((uintptr_t)entity + 0xA0) = entity->origin();
		*(int*)((uintptr_t)entity + 0xA68) = 0;
		*(int*)((uintptr_t)entity + 0xA30) = 0;
		entity->invalidate_bone_cache();
		entity->SetupBones(record.boneMatrix, 128, BONE_USED_BY_ANYTHING, g_GlobalVars->curtime);

		math::vector_transform(hitbox_center, record.boneMatrix[hitbox_head->bone], record.hitbox_position);

		data[i].push_front(record);
	}
	
	float best_fov = 180.0f;

	for (auto& node : data) 
	{
		auto& cur_data = node.second;

		if (cur_data.empty())
		{
			continue;
		}

		for (auto& bd : cur_data)
		{
			if (std::fabsf(delta_time) > 0.2f)
			{
				continue;
			}

			float fov = math::calculate_fov(csgo::local_player->get_eye_pos(), bd.hitbox_position, cmd->viewangles);

			if (fov < best_fov)
			{
				best_fov = fov;
				cmd->tick_count = TIME_TO_TICKS(bd.sim_time + lerp_time);
			}
		}
	} 
}