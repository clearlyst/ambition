#include "aimbot.hpp"

bool smokecheck(Vector startPos, Vector endPos)
{
	static auto LineGoesThroughSmokeFn = (bool(*)(Vector, Vector))Utils::PatternScan2("client.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0");
	return LineGoesThroughSmokeFn(startPos, endPos);
}

variables::config::aimbot::aimbot_value_t aimbot::get_current_settings()
{
	const auto general_settings = variables::config::aimbot::general;
	const auto pistol_settings = variables::config::aimbot::pistols;
	const auto pistol_heavy_settings = variables::config::aimbot::heavy_pistols;
	const auto smgs_settings = variables::config::aimbot::smg;
	const auto shotguns_settings = variables::config::aimbot::shotguns;
	const auto rifle_settings = variables::config::aimbot::rifles;
	const auto sniper_settings = variables::config::aimbot::snipers;

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

void aimbot::run(CUserCmd* cmd)
{
	const auto current_settings = this->get_current_settings();
	const auto recoil_scale = g_CVar->FindVar(xorstr("weapon_recoil_scale"))->GetFloat();
	int best_distance = INT_MAX;
	int best_health = INT_MAX;
	float best_fov = current_settings.fov;
	float best_backtrack_fov = current_settings.fov;
	Vector best_target = Vector(0, 0, 0);

	if (!variables::config::aimbot::enable)
	{
		return;
	}

	
	if (variables::config::aimbot::shootataimkey ? cmd->buttons & IN_ATTACK : Utils::bind(variables::config::aimbot::key, variables::config::aimbot::key_type))
	{

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

		std::vector<int> hitboxes;

		hitboxes.clear();

		if (current_settings.head)
		{
			hitboxes.push_back(HITBOX_HEAD);
		}

		if (current_settings.neck)
		{
			hitboxes.push_back(HITBOX_NECK);
		}

		if (current_settings.chest)
		{
			hitboxes.push_back(HITBOX_UPPER_CHEST);
			hitboxes.push_back(HITBOX_CHEST);
			hitboxes.push_back(HITBOX_LOWER_CHEST);
		}

		if (current_settings.stomach)
		{
			hitboxes.push_back(HITBOX_STOMACH);
		}

		if (current_settings.pelvis)
		{
			hitboxes.push_back(HITBOX_PELVIS);
		}

		if (current_settings.foot)
		{
			hitboxes.push_back(HITBOX_LEFT_FOOT);
			hitboxes.push_back(HITBOX_RIGHT_FOOT);
		}

		if (hitboxes.empty())
		{
			return;
		}

		for (auto i = 1; i < g_GlobalVars->maxClients; i++)
		{
			player_t* entity = player_t::GetPlayerByIndex(i);

			if (!entity || !entity->is_alive() || !entity->is_player() || entity == csgo::local_player || entity->has_gun_game_immunity() || entity->IsDormant())
			{
				continue;
			}

			if (entity->team() == csgo::local_player->team() && !current_settings.teammates)
			{
				continue;
			}

			if (!(entity->flags() & FL_ONGROUND) && current_settings.enemyinair)
			{
				continue;
			}

			if (!(csgo::local_player->flags() & FL_ONGROUND) && current_settings.selfinair)
			{
				continue;
			}

			if (csgo::local_player->flash_duration() > 1.f && current_settings.flashcheck)
			{
				continue;
			}

			for (auto hitbox : hitboxes)
			{
				Vector get_hitbox_position = entity->get_hitbox_position(hitbox);

				if (current_settings.smokecheck && smokecheck(csgo::local_player->get_eye_pos(), get_hitbox_position))
				{
					return;
				}

				if (!csgo::local_player->can_see_player_pos(entity, get_hitbox_position))
				{
					if (!current_settings.autowall)
					{
						continue;
					}

				}

				const auto distance = (entity->origin() - csgo::local_player->origin()).Length();
				const auto health = entity->health();

				float fov = math::calculate_fov(csgo::local_player->get_eye_pos(), get_hitbox_position, cmd->viewangles);

				switch (current_settings.priority)
				{
				case 0:
					if (fov < best_fov)
					{
						best_target = get_hitbox_position;
						best_fov = fov;
					}
					break;
				case 1:
					if (distance < best_distance)
						{
							if (fov < best_fov)
							{
								best_target = get_hitbox_position;
								best_fov = fov;
								best_distance = distance;
							}
						}
					break;
				case 2:
					if (health < best_health)
						{
							if (fov < best_fov)
							{
								best_target = get_hitbox_position;
								best_fov = fov;
								best_health = health;
							}
						}
					break;
				}
			}
		}

		if (best_target.is_zero())
		{
			return;
		}

		 auto calculated_angle = math::calculate_angle(csgo::local_player->get_eye_pos(), best_target, cmd->viewangles).clamped();

		if (current_settings.smooth != 0)
		{
			calculated_angle /= current_settings.smooth;
		}

		if (current_settings.compensaterecoil)
		{
			if (current_settings.smooth != 0)
			{
				calculated_angle -= (csgo::local_player->aim_punch_angle() * recoil_scale) / current_settings.smooth;
			}
			else
			{
				calculated_angle -= (csgo::local_player->aim_punch_angle() * recoil_scale);
			}
		}

		cmd->viewangles += calculated_angle.clamped();

		if (!current_settings.silent)
		{
			g_EngineClient->SetViewAngles(cmd->viewangles);
		}
	}
}