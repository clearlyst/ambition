#include "triggerbot.hpp"

bool checkinsmoke(Vector startPos, Vector endPos)
{
	static auto LineGoesThroughSmokeFn = (bool(*)(Vector, Vector))Utils::PatternScan2("client.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0");
	return LineGoesThroughSmokeFn(startPos, endPos);
}

variables::config::triggerbot::triggerbot_value_t triggerbot::get_current_settings()
{
	const auto general_settings = variables::config::triggerbot::general;
	const auto pistol_settings = variables::config::triggerbot::pistols;
	const auto pistol_heavy_settings = variables::config::triggerbot::heavy_pistols;
	const auto smgs_settings = variables::config::triggerbot::smg;
	const auto shotguns_settings = variables::config::triggerbot::shotguns;
	const auto rifle_settings = variables::config::triggerbot::rifles;
	const auto sniper_settings = variables::config::triggerbot::snipers;

	const auto active_weapon = csgo::local_player->active_weapon();

	if (!active_weapon)
	{
		return general_settings;
	}

	const auto weapon_type = active_weapon->get_weapon_type();

	if (!weapon_type)
	{
		return general_settings;
	}

	const auto is_pistol = weapon_type == WEAPON_TYPE_PISTOL;
	const auto is_heavy_pistol = weapon_type == WEAPON_TYPE_HEAVYPISTOL;
	const auto is_smg = weapon_type == WEAPON_TYPE_SMG;
	const auto is_shotgun = weapon_type == WEAPON_TYPE_SHOTGUN;
	const auto is_rifle = weapon_type == WEAPON_TYPE_RIFLE;
	const auto is_sniper = weapon_type == WEAPON_TYPE_SNIPER;

	if (is_pistol && pistol_settings.override_general)
	{
		return pistol_settings;
	}

	if (is_heavy_pistol && pistol_heavy_settings.override_general)
	{
		return pistol_heavy_settings;
	}

	if (is_smg && smgs_settings.override_general)
	{
		return smgs_settings;
	}

	if (is_shotgun && shotguns_settings.override_general)
	{
		return shotguns_settings;
	}

	if (is_rifle && rifle_settings.override_general)
	{
		return rifle_settings;
	}

	if (is_sniper && sniper_settings.override_general)
	{
		return sniper_settings;
	}

	return general_settings;
}

void triggerbot::run(CUserCmd* cmd)
{
	if (!variables::config::triggerbot::enable || !Utils::bind(variables::config::triggerbot::key, variables::config::triggerbot::key_type))
	{
		return;
	}

	if (!g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
	{
		return;
	}

	if (!csgo::local_player || !csgo::local_player->is_alive() || csgo::local_player->is_defusing())
	{
		return;
	}

	if (menu::get().IsVisible())
	{
		return;
	}

	bool hitbox;

	const auto current_settings = this->get_current_settings();
	const auto recoil_scale = g_CVar->FindVar(xorstr("weapon_recoil_scale"))->GetFloat();

	auto weapon = csgo::local_player->active_weapon();

	if (!weapon || !weapon->isgun() || weapon->clip1_count() == 0)
	{
		return;
	}

	auto weapon_data = weapon->get_weapon_data();

	if (!weapon_data)
	{
		return;
	}

	Vector src, dst, forward;
	trace_t trace;
	Ray_t ray;
	CTraceFilter filter;

	math::angle_vectors(cmd->viewangles + csgo::local_player->aim_punch_angle() * recoil_scale, forward);
	forward *= weapon->get_weapon_data()->m_flRange;
	filter.pSkip = csgo::local_player;
	src = csgo::local_player->get_eye_pos();
	dst = src + forward;

	ray.Init(src, dst);
    g_EngineTrace->TraceRay(ray, 0x46004003, &filter, &trace);

	auto entity = reinterpret_cast<player_t*>(trace.hit_entity);

	if (!entity || !entity->is_alive() || !entity->is_player() || entity == csgo::local_player || entity->has_gun_game_immunity() || entity->IsDormant())
	{
		return;
	}

	if (entity->team() == csgo::local_player->team() && !current_settings.teammates)
	{
		return;
	}

	if (!(entity->flags() & FL_ONGROUND) && current_settings.enemyinair)
	{
		return;
	}

	if (!(csgo::local_player->flags() & FL_ONGROUND) && current_settings.selfinair)
	{
		return;
	}

	if (checkinsmoke(csgo::local_player->get_eye_pos(), trace.endpos) && current_settings.smokecheck)
	{
		return;
	}

	if (csgo::local_player->flash_duration() > 1.f && current_settings.flashcheck)
	{
		return;
	}

	if (current_settings.autopistol)
	{
		if (weapon->get_weapon_data()->m_iWeaponType == CSWeaponType::WEAPONTYPE_PISTOL)
		{
			const float server_time = csgo::local_player->get_tick_base() * g_GlobalVars->interval_per_tick;
			const float next_shot = weapon->next_primary_attack() - server_time;

			if (next_shot > 0)
			{
				if (weapon->item_definition_index() == ItemDefinitionIndex::WEAPON_REVOLVER)
				{
					cmd->buttons &= ~IN_ATTACK2;
				}
				else
				{
					cmd->buttons &= ~IN_ATTACK;
				}
			}
		}
	}

	switch (trace.hitgroup)
	{
	case HITGROUP_HEAD:
		hitbox = current_settings.head;
		break;
	case HITGROUP_NECK:
		hitbox = current_settings.neck;
		break;
	case HITGROUP_CHEST:
		hitbox = current_settings.chest;
		break;
	case HITGROUP_STOMACH:
		hitbox = current_settings.stomach;
		break;
	case HITGROUP_LEFTLEG:
	case HITGROUP_RIGHTLEG:
		hitbox = current_settings.foot;
		break;
	default:
		hitbox = false;
	}

	if (!hitbox)
	{
		return;
	}

	if (hitbox)
	{
		cmd->buttons |= IN_ATTACK;
	}
}