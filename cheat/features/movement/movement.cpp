#include "movement.hpp"

void restore_to_predicted_frame(int predicted_frame) 
{
	static auto restore = reinterpret_cast<DWORD(__stdcall*)(int, int)>(Utils::PatternScan2(xorstr("client.dll"), xorstr("55 8b ec 8b 4d ? 56 e8 ? ? ? ? 8b 75")));
	restore(0, predicted_frame);
}

void movement::bunnyhop(CUserCmd* cmd)
{
	if (!variables::config::movement::bunnyhop || !g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return;
	}

	if (Utils::bind(variables::config::movement::jumpbug_key, variables::config::movement::jumpbug_key_type))
	{
		return;
	}

	if (Utils::bind(variables::config::movement::ladderedgejump_key, variables::config::movement::ladderedgejump_key_type))
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		return;
	}

	static bool bLastJumped = false;
	static bool bShouldFake = false;

	if (!bLastJumped && bShouldFake)
	{
		bShouldFake = false;
        cmd->buttons |= IN_JUMP;
	}
	else if (cmd->buttons & IN_JUMP)
	{
		if (csgo::local_player->flags() & FL_ONGROUND)
		{
			bShouldFake = bLastJumped = true;
		}
		else
		{
			cmd->buttons &= ~IN_JUMP;
			bLastJumped = false;
		}
	}
	else
	{
		bShouldFake = bLastJumped = false;
	}
}

void blockbuttons()
{
	if (variables::config::movement::blockbutton_forward)
	{
		g_EngineClient->ExecuteClientCmd(xorstr("-forward"));
	}

	if (variables::config::movement::blockbutton_back)
	{
		g_EngineClient->ExecuteClientCmd(xorstr("-back"));
	}

	if (variables::config::movement::blockbutton_left)
	{
		g_EngineClient->ExecuteClientCmd(xorstr("-moveleft"));
	}

	if (variables::config::movement::blockbutton_right)
	{
		g_EngineClient->ExecuteClientCmd(xorstr("-moveright"));
	}
}

void movement::resetdetection()
{
	if (!variables::config::movement::edgejump || !Utils::bind(variables::config::movement::edgejump_key, variables::config::movement::edgejump_key_type))
	{
		movement::get().ejsuccesful = 0;
	}

	if (!variables::config::movement::minijump || !Utils::bind(variables::config::movement::minijump_key, variables::config::movement::minijump_key_type))
	{
		movement::get().mjsuccesful = 0;
	}

	if (!variables::config::movement::longjump || !Utils::bind(variables::config::movement::longjump_key, variables::config::movement::longjump_key_type))
	{
		movement::get().ljsuccesful = 0;
	}

	if (!variables::config::movement::jumpbug || !Utils::bind(variables::config::movement::jumpbug_key, variables::config::movement::jumpbug_key_type))
	{
		movement::get().jbsuccesful = 0;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		movement::get().ljsuccesful = 0;
		movement::get().ejsuccesful = 0;
		movement::get().jbsuccesful = 0;
		movement::get().mjsuccesful = 0;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		movement::get().ljsuccesful = 0;
		movement::get().ejsuccesful = 0;
		movement::get().jbsuccesful = 0;
		movement::get().mjsuccesful = 0;
	}

	if (csgo::local_player->flags() & FL_ONGROUND)
	{
		movement::get().ljsuccesful = 0;
		movement::get().ejsuccesful = 0;
		movement::get().jbsuccesful = 0;
		movement::get().mjsuccesful = 0;
	}
}

void movement::edgejump(CUserCmd* cmd)
{
	if (!variables::config::movement::edgejump || !Utils::bind(variables::config::movement::edgejump_key, variables::config::movement::edgejump_key_type))
	{
		return;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		return;
	}

	if ((engine_prediction::get().data.m_fFlags & FL_ONGROUND) && !(csgo::local_player->flags() & FL_ONGROUND))
	{
		cmd->buttons |= IN_JUMP;

		movement::get().ejsuccesful = 1;

		if (variables::config::movement::edgejump_blockbuttons)
		{
			blockbuttons();
		}
	}
}

void movement::minijump(CUserCmd* cmd)
{
	if (!variables::config::movement::minijump || !Utils::bind(variables::config::movement::minijump_key, variables::config::movement::minijump_key_type))
	{
		return;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		return;
	}

	if ((engine_prediction::get().data.m_fFlags & FL_ONGROUND) && !(csgo::local_player->flags() & FL_ONGROUND))
	{
		cmd->buttons |= IN_DUCK;

		movement::get().mjsuccesful = 1;

		if (variables::config::movement::minijump_blockbuttons)
		{
			blockbuttons();
		}

		if (variables::config::movement::minijump_forceedgejump)
		{
			cmd->buttons |= IN_JUMP;
		}
	}
}

void movement::longjump(CUserCmd* cmd)
{
	static int ticks = 0;
	static bool duck = false;

	if (!variables::config::movement::longjump || !Utils::bind(variables::config::movement::longjump_key, variables::config::movement::longjump_key_type))
	{
		return;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		return;
	}

	if ((engine_prediction::get().data.m_fFlags & FL_ONGROUND) && !(csgo::local_player->flags() & FL_ONGROUND))
	{
		ticks = cmd->tick_count + 2;
		duck = true;
		cmd->buttons |= IN_DUCK;

		movement::get().ljsuccesful = 1;

		if (variables::config::movement::longjump_blockbuttons)
		{
			blockbuttons();
		}

		if (variables::config::movement::longjump_forceedgejump)
		{
			cmd->buttons |= IN_JUMP;
		}
	}

	if (duck && (cmd->tick_count < ticks))
	{
		cmd->buttons |= IN_DUCK;
	}
	else
	{
		duck = false;
	}
}

void movement::ladderedgejump(CUserCmd* cmd)
{
	if (!variables::config::movement::ladderedgejump || !Utils::bind(variables::config::movement::ladderedgejump_key, variables::config::movement::ladderedgejump_key_type))
	{
		return;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		return;
	}

	if ((engine_prediction::get().data.m_nMoveType == MOVETYPE_LADDER) && (csgo::local_player->move_type() != MOVETYPE_LADDER))
	{
		cmd->buttons |= IN_JUMP;
	}
}

void movement::jumpbug(CUserCmd* cmd)
{
	if (!variables::config::movement::jumpbug || !Utils::bind(variables::config::movement::jumpbug_key, variables::config::movement::jumpbug_key_type))
	{
		return;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		return;
	}

	if (!(engine_prediction::get().data.m_fFlags & FL_ONGROUND) && csgo::local_player->flags() & FL_ONGROUND)
	{
		cmd->buttons |= IN_DUCK;
		cmd->buttons &= ~IN_JUMP;
	}

	jbsuccesful = (!(edgebug_should || pixelsurf_should) && csgo::local_player->velocity().z > engine_prediction::get().data.m_vecVelocity.z && !(engine_prediction::get().data.m_fFlags & FL_ONGROUND) && !(csgo::local_player->flags() & FL_ONGROUND) && csgo::local_player->move_type() != MOVETYPE_NOCLIP && csgo::local_player->move_type() != MOVETYPE_OBSERVER) ? 1 : 0;

	if (jbsuccesful == 1)
	{
		//notify::get().run("jumpbugged", true, true, false);
	}
}

void movement::autoduck(CUserCmd* cmd)
{
	if (!variables::config::movement::autoduck || !Utils::bind(variables::config::movement::autoduck_key, variables::config::movement::autoduck_key_type))
	{
		return;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		return;
	}

	if (Utils::bind(variables::config::movement::edgebug_key, variables::config::movement::edgebug_key_type) || Utils::bind(variables::config::movement::minijump_key, variables::config::movement::minijump_key_type) || Utils::bind(variables::config::movement::jumpbug_key, variables::config::movement::jumpbug_key_type))
	{
		return;
	}

	for (int i = 0; i < TIME_TO_TICKS(variables::config::movement::autoduck_time); i++)
	{
		if (!(engine_prediction::get().data.m_fFlags & FL_ONGROUND) && (csgo::local_player->flags() & FL_ONGROUND))
		{
			cmd->buttons |= IN_DUCK;
		}
	}
}

void movement::infinityduck(CUserCmd* cmd)
{
	if (!variables::config::movement::infinityduck)
	{
		return;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		return;
	}

	cmd->buttons |= IN_BULLRUSH;
}

bool edgebug_detection(CUserCmd* cmd)
{
	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return false;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		return false;
	}

	if (csgo::local_player->flags() & FL_ONGROUND || engine_prediction::get().data.m_fFlags & FL_ONGROUND)
	{
		return false;
	}

	static ConVar* sv_gravity = g_CVar->FindVar(xorstr("sv_gravity"));

	float gravity_vel = (sv_gravity->GetFloat() * 0.5f * g_GlobalVars->interval_per_tick);

	if (engine_prediction::get().data.m_vecVelocity.z < -gravity_vel && round(csgo::local_player->velocity().z) == -round(gravity_vel))
	{
		return true;
	}

	if (engine_prediction::get().data.m_vecVelocity.z < -5.62895 && csgo::local_player->velocity().z > engine_prediction::get().data.m_vecVelocity.z && csgo::local_player->velocity().z < -8.293333)
	{
		float velocty_before_engineprediction = csgo::local_player->velocity().z;

		engine_prediction::get().repredict(cmd);
		engine_prediction::get().restore();

		static auto sv_gravity_after_engineprediction = g_CVar->FindVar(xorstr("sv_gravity"));
		const float gravity_velocity_constant = roundf(-sv_gravity_after_engineprediction->GetFloat() * g_GlobalVars->interval_per_tick + velocty_before_engineprediction);

		if (gravity_velocity_constant == round(csgo::local_player->velocity().z))
		{
			return true;
		}
	}

	return false;
}

void movement::pre_prediction(CUserCmd* cmd)
{
	if (!csgo::local_player)
	{
		return;
	}

	if (edgebug_should && should_duck_next)
	{
		cmd->buttons |= IN_DUCK;
	}

	if (pixelsurf_should)
	{
		cmd->buttons |= IN_DUCK;
	}
}

void movement::autoedgebug(CUserCmd* cmd)
{
	struct movement_vars_t
	{
		Vector viewangles;
		Vector view_delta;
		float forwardmove;
		float sidemove;
		int buttons;
	};

	static movement_vars_t bmove;
	movement_vars_t omove;
	omove.viewangles = cmd->viewangles;
	omove.view_delta = (cmd->viewangles - edgebug_old_viewangles);
	omove.forwardmove = cmd->forwardmove;
	omove.sidemove = cmd->sidemove;
	omove.buttons = cmd->buttons;

	if (!edgebug_should)
	{
		bmove = omove;
	}

	if (!variables::config::movement::edgebug || !Utils::bind(variables::config::movement::edgebug_key, variables::config::movement::edgebug_key_type))
	{
		edgebug_should = false;
		return;
	}

	if (!csgo::local_player || !csgo::local_player->is_alive() || !g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
	{
		edgebug_should = false;
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		edgebug_should = false;
		return;
	}

	Vector current_angles;

	int edgebug_pred_cound = 0;
	float highest_ground = 0.f;
	int search_dir = 0;
	int last_pred_ground = 0;

	for (int t = 0; edgebug_pred_cound < variables::config::movement::edgebug_ticks; t++)
	{
		restore_to_predicted_frame(g_Prediction->m_nCommandsPredicted() - 1);

		static int last_type = 0;

		if (edgebug_should)
		{
			t = last_type;
		}

		bool do_strafe = variables::config::movement::edgebug_strafetoedge ? (t < 2 || t > 3) : false;
		bool do_duck = t == 1 || t == 3;

		if (t > 3)
		{
			if (last_pred_ground < 2)
			{
				break;
			}

			bmove.view_delta += (bmove.view_delta / 2) * search_dir;
		}

		current_angles = bmove.viewangles;

		for (int i = 0; i < variables::config::movement::edgebug_ticks && edgebug_pred_cound < variables::config::movement::edgebug_ticks; i++)
		{
			if (do_strafe)
			{
				current_angles += bmove.view_delta;
				cmd->forwardmove = bmove.forwardmove;
				cmd->sidemove = bmove.sidemove;

				Vector backup_viewangles = cmd->viewangles;
				cmd->viewangles = current_angles;
				math::start_movement_fix(cmd);
				cmd->viewangles = backup_viewangles;
				math::end_movement_fix(cmd);
			}
			else
			{
				cmd->forwardmove = 0.f;
				cmd->sidemove = 0.f;
			}

			if (do_duck)
			{
				cmd->buttons |= IN_DUCK;
			}
			else
			{
				cmd->buttons &= ~IN_DUCK;
			}

			engine_prediction::get().repredict(cmd);
			edgebug_should = edgebug_detection(cmd);
			engine_prediction::get().restore();

			edgebug_pred_cound++;

			if (!edgebug_should && t > 3 && csgo::local_player->origin().z < highest_ground)
			{
				search_dir = -1;
				break;
			}

			if (csgo::local_player->flags() & FL_ONGROUND)
			{
				if (t == 0)
				{
					highest_ground = csgo::local_player->origin().z;
				}

				if (t == 2)
				{
					search_dir = csgo::local_player->origin().z < highest_ground ? -1 : 1;
				}

				if (t > 3)
				{
					search_dir = 1;

					if (csgo::local_player->origin().z < highest_ground)
					{
						search_dir = -1;
					}
					else
					{
						highest_ground = csgo::local_player->origin().z;
					}
				}

				last_pred_ground = i;

				break;
			}

			if (csgo::local_player->move_type() == MOVETYPE_NOCLIP || csgo::local_player->move_type() == MOVETYPE_LADDER)
			{
				break;
			}

			if (edgebug_should)
			{
				if (t < 4)
				{
					last_type = t;
				}
				else
				{
					last_type = 0;
				}
				 
				should_duck_next = do_duck;

				if (do_strafe)
				{
					cmd->forwardmove = bmove.forwardmove;
					cmd->sidemove = bmove.sidemove;
					cmd->viewangles = bmove.viewangles + bmove.view_delta;

					bmove.viewangles = cmd->viewangles;
				}

				edgebug_tick = g_GlobalVars->tickcount + (i + 1);
				edgebug_prediction_ticks = i;
				edgebug_prediction_timestamp = g_GlobalVars->tickcount;
				edgebug_mouse_offset = std::abs(cmd->mousedx);

				return;
			}
		}
	}

	cmd->viewangles = omove.viewangles;
	cmd->forwardmove = omove.forwardmove;
	cmd->sidemove = omove.sidemove;
	cmd->buttons = omove.buttons;
}

void movement::autoedgebug_lock(float& x, float& y)
{
	if (!variables::config::movement::edgebug || !Utils::bind(variables::config::movement::edgebug_key, variables::config::movement::edgebug_key_type))
	{
		return;
	}

	if (!csgo::local_player || !csgo::local_player->is_alive() || !g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		return;
	}

	if (edgebug_should)
	{
		if (x != 0.0)
		{
			float v3 = (float)(edgebug_prediction_timestamp + edgebug_prediction_ticks - g_GlobalVars->tickcount) / x;
			float v4 = 100.0 / (atan2f(edgebug_prediction_ticks, v3) + 100.0 + (float)(variables::config::movement::edgebug_lock * edgebug_mouse_offset));
			if (!isnan(v4))
				x = x * v4;
		}

		if (y != 0.0)
		{
			y *= (1.f - (variables::config::movement::edgebug_lock / 100.f));
		}
	}
}

void movement::autoalign(CUserCmd* cmd)
{
	if (!variables::config::movement::autoalign || !Utils::bind(variables::config::movement::autoalign_key, variables::config::movement::autoalign_key_type))
	{
		return;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		return;
	}

	if (engine_prediction::get().data.m_fFlags & FL_ONGROUND)
	{
		return;
	}

	bool Awall = false;
	CGameTrace trace;
	float step = (float)M_PI * 2.0f / 8.f;
	bool checkAg = false;
	static float StartCircle = 0.f;

	if (csgo::local_player->velocity().z != -6.25f && engine_prediction::get().data.m_vecVelocity.z != -6.25f)
	{
		StartCircle = 0.f;
	}

	for (int i = 0; i < 72; i++)
	{
		if (Awall)
		{
			break;
		}

		for (float a = StartCircle; a < (M_PI * 2.0f); a += step)
		{
			Vector wishdir = Vector(17.f * cosf(a), 17.f * sinf(a), 0.f);

			const auto startPos = Vector(csgo::local_player->abs_origin().x, csgo::local_player->abs_origin().y, csgo::local_player->abs_origin().z + i);
			const auto endPos = startPos + wishdir;

			CTraceFilterWorldOnly flt;

			Ray_t ray;
			ray.Init(startPos, endPos);
			g_EngineTrace->TraceRay(ray, MASK_PLAYERSOLID, &flt, &trace);

			if ((trace.fraction < 1.f) && (trace.plane.normal.z == 0.f))
			{
				StartCircle = a;
				Awall = true;
				checkAg = true;
				break;
			}
		}
	}

	if (Awall)
	{
		Vector NormalPlane = Vector(trace.plane.normal.x * -1.f, trace.plane.normal.y * -1.f, 0.f);
		Vector WallAngle = NormalPlane.toAngle();

		if (csgo::local_player->velocity().Length2D() > 280 && !(cmd->buttons & IN_DUCK))
		{
			if (csgo::local_player->velocity().z == -6.25f || engine_prediction::get().data.m_vecVelocity.z == -6.25f)
			{
				float mVel = hypotf(csgo::local_player->velocity().x, csgo::local_player->velocity().y);
				float ideal = RAD2DEG(atanf(25.f / mVel));
				Vector dvelo = csgo::local_player->velocity();
				dvelo.z = 0.f;
				Vector velo_angle = dvelo.toAngle();
				Vector delta = velo_angle - WallAngle;
				delta.normalize();

				if (delta.y >= 0.f)
				{
					WallAngle.y += ideal;
				}
				else
				{
					WallAngle.y -= ideal;
				}
			}
		}

		float rotation = DEG2RAD(WallAngle.y - cmd->viewangles.y);
		float cos_rot = cos(rotation);
		float sin_rot = sin(rotation);
		float multiplayer = 0.f;

		if (csgo::local_player->velocity().z == -6.25f || engine_prediction::get().data.m_vecVelocity.z == -6.25f)
		{
			multiplayer = 45.f;
		}
		else
		{
			multiplayer = 6.f;
		}

		float forwardmove = cos_rot * multiplayer;
		float sidemove = -sin_rot * multiplayer;

		if (trace.fraction > 0.94f || !(cmd->buttons & IN_FORWARD) && !(cmd->buttons & IN_BACK) && !(cmd->buttons & IN_MOVELEFT) && !(cmd->buttons & IN_MOVERIGHT))
		{
			cmd->forwardmove = forwardmove;
			cmd->sidemove = sidemove;
		}

		if (csgo::local_player->velocity().Length2D() > 280 && !(cmd->buttons & IN_DUCK))
		{
			if (csgo::local_player->velocity().z == -6.25f || engine_prediction::get().data.m_vecVelocity.z == -6.25f)
			{
				if (cmd->forwardmove < 0.f && cmd->buttons & IN_FORWARD)
				{
					cmd->forwardmove = 450.f;
				}

				if (cmd->forwardmove > 0.f && cmd->buttons & IN_BACK)
				{
					cmd->forwardmove = -450.f;
				}

				if (cmd->sidemove < 0.f && cmd->buttons & IN_MOVERIGHT)
				{
					cmd->sidemove = 450.f;
				}

				if (cmd->sidemove > 0.f && cmd->buttons & IN_MOVELEFT)
				{
					cmd->sidemove = -450.f;
				}

				return;
			}
		}

		if (multiplayer == 45.f && (cmd->buttons & IN_FORWARD) || (cmd->buttons & IN_BACK) || (cmd->buttons & IN_MOVELEFT) || (cmd->buttons & IN_MOVERIGHT))
		{
			int buttons = cmd->buttons;

			float forwardmove = cmd->forwardmove;
			float sidemove = cmd->sidemove;

			for (int i = 0; i < 450; i += 45)
			{
				restore_to_predicted_frame(g_Prediction->m_nCommandsPredicted() - 1);

				if (buttons & IN_FORWARD)
				{
					cmd->forwardmove = i;
				}

				if (buttons & IN_BACK)
				{
					cmd->forwardmove = -i;
				}

				if (buttons & IN_MOVELEFT)
				{
					cmd->sidemove = -i;
				}

				if (buttons & IN_MOVERIGHT)
				{
					cmd->sidemove = i;
				}

				engine_prediction::get().repredict(cmd);
				engine_prediction::get().restore();

				float zvelo = csgo::local_player->velocity().z;

				if (zvelo == -engine_prediction::get().data.m_vecVelocity.z)
				{
					forwardmove = cmd->forwardmove;
					sidemove = cmd->sidemove;
				}
			}

			cmd->forwardmove = forwardmove;
			cmd->sidemove = sidemove;
		}


		if (cmd->forwardmove < 0.f && cmd->buttons & IN_FORWARD)
		{
			cmd->forwardmove = 450.f;
		}

		if (cmd->forwardmove > 0.f && cmd->buttons & IN_BACK)
		{
			cmd->forwardmove = -450.f;
		}

		if (cmd->sidemove < 0.f && cmd->buttons & IN_MOVERIGHT)
		{
			cmd->sidemove = 450.f;
		}

		if (cmd->sidemove > 0.f && cmd->buttons & IN_MOVELEFT)
		{
			cmd->sidemove = -450.f;
		}
	}
}

void movement::autopixelsurf(CUserCmd* cmd)
{
	static int ticks;

	if (!variables::config::movement::pixelsurf || !Utils::bind(variables::config::movement::pixelsurf_key, variables::config::movement::pixelsurf_key_type))
	{
		return;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		return;
	}

	if (Utils::bind(variables::config::movement::edgebug_key, variables::config::movement::edgebug_key_type))
	{
		ticks = 0;
		return;
	}

	if (!pixelsurf_should)
	{
		int BackupButtons = cmd->buttons;

		for (int type = 0; type < 2; type++)
		{
			restore_to_predicted_frame(g_Prediction->m_nCommandsPredicted() - 1);

			if (type == 0)
			{
				cmd->buttons &= ~IN_DUCK;
			}
			else
			{
				cmd->buttons |= IN_DUCK;
			}

			for (int ticks = 0; ticks < 4; ticks++)
			{
				engine_prediction::get().repredict(cmd);
				engine_prediction::get().restore();

				if (csgo::local_player->flags() & FL_ONGROUND)
				{
					break;
				}

				float zVelo = csgo::local_player->velocity().z;

				pixelsurf_should = engine_prediction::get().data.m_vecVelocity.z < 10.f && zVelo == -6.25f;

				if (pixelsurf_should && type == 0)
				{
					pixelsurf_should = false;
					cmd->buttons = BackupButtons;
					return;
				}

				if (pixelsurf_should)
				{
					ticks = cmd->tick_count + ticks + 16;
					BackupButtons = cmd->buttons;
					break;
				}
			}
		}

		cmd->buttons = BackupButtons;
	}
	else
	{
		cmd->buttons |= IN_DUCK;

		if (cmd->tick_count > ticks)
		{
			if (engine_prediction::get().data.m_vecVelocity.z != -6.25f)
			{
				pixelsurf_should = false;
			}
		}
	}
}

void movement::staminahop(CUserCmd* cmd)
{
	static int ticks;
	static bool set = false;

	if (!variables::config::movement::staminahop || !Utils::bind(variables::config::movement::staminahop_key, variables::config::movement::staminahop_key_type))
	{
		return;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP)
	{
		return;
	}

	if (csgo::local_player->flags() & FL_ONGROUND && !set)
	{
		ticks = g_GlobalVars->tickcount;
		set = true;
	}

	if (g_GlobalVars->tickcount - ticks > variables::config::movement::staminahop_ticks && csgo::local_player->flags() & FL_ONGROUND)
	{
		cmd->buttons |= IN_JUMP;
		set = false;
	}
}

void movement::mousespeedlimiter(float& x, float& y)
{
	if (!variables::config::movement::msl || !Utils::bind(variables::config::movement::msl_key, variables::config::movement::msl_key_type))
	{
		return;
	}

	if (!csgo::local_player || !csgo::local_player->is_alive() || !g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP || csgo::local_player->flags() & FL_ONGROUND)
	{
		return;
	}

	x = std::clamp< float >(x, -variables::config::movement::msl_strength_x, variables::config::movement::msl_strength_x);
	y = std::clamp< float >(y, -variables::config::movement::msl_strength_y, variables::config::movement::msl_strength_y);
}

void movement::blockbot(CUserCmd* cmd)
{
	if (!variables::config::movement::blockbot || !Utils::bind(variables::config::movement::blockbot_key, variables::config::movement::blockbot_key_type))
	{
		return;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return;
	}

	float best_dist = std::numeric_limits<float>::max();
	int best_target = -1;

	for (int i = 1; i < g_GlobalVars->maxClients; i++)
	{
		auto entity = reinterpret_cast<player_t*>(g_EntityList->GetClientEntity(i));

		if (!entity || entity->IsDormant() || !entity->is_alive() || entity == csgo::local_player)
		{
			continue;
		}

		float dist = csgo::local_player->origin().DistTo(entity->origin());

		if (dist < best_dist)
		{
			best_dist = dist;
			best_target = i;
		}
	}

	auto entity = reinterpret_cast<player_t*>(g_EntityList->GetClientEntity(best_target));

	if (!entity)
	{
		return;
	}

	const float speed = entity->velocity().Length();
	const auto forward = entity->origin() - csgo::local_player->origin();

	if (entity->get_bone_position(6).z < csgo::local_player->origin().z && csgo::local_player->origin().DistTo(entity->origin()) < 100.f)
	{
		cmd->forwardmove = ((sin(DEG2RAD(cmd->viewangles.y)) * forward.y) + (cos(DEG2RAD(cmd->viewangles.y)) * forward.x)) * speed;
		cmd->sidemove = ((cos(DEG2RAD(cmd->viewangles.y)) * -forward.y) + (sin(DEG2RAD(cmd->viewangles.y)) * forward.x)) * speed;
	}
	else
	{
		auto yaw_delta = (atan2(forward.y, forward.x) * 180.0f / 3.14159265359f) - cmd->viewangles.y;

		if (yaw_delta > 180)
		{
			yaw_delta -= 360;
		}
		else if (yaw_delta < -180)
		{
			yaw_delta += 360;
		}

		if (yaw_delta > 0.25)
		{
			cmd->sidemove = -speed;
		}
		else if (yaw_delta < -0.25)
		{
			cmd->sidemove = speed;
		}
	}
}
float height;
float distance;
bool strafe_left;
bool strafe_right;
bool calcheight;
bool last_jumping = false;
int dead_time_air; 
int saved_tick_count_air;
int pre_velocity;
int max_velocity;
int strafes;
int syncticks;
int durationticks;
int durationticks2;
int lastvelosynced;
int savedongroundtick;
Vector jumpposheight;
Vector jump_positions[1];
int bhops = 0;
bool bhop;
bool multibhop;

float float_max(float value1, float value2)
{
	if (value1 >= value2)
	{
		return value1;
	}

	return value2;
}

void movement::jumpstats(CUserCmd* cmd)
{
	if (!variables::config::movement::jumpstats)
	{
		return;
	}

	if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
	{
		return;
	}

	if (csgo::local_player->flags() & FL_INWATER || csgo::local_player->flags() & FL_WATERJUMP || csgo::local_player->flags() & FL_FROZEN)
	{
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP || csgo::local_player->move_type() == MOVETYPE_OBSERVER)
	{
		return;
	}

	static auto sv_accelerate = g_CVar->FindVar(xorstr("sv_accelerate"));
	static auto sv_accelerate_use_weapon_speed = g_CVar->FindVar(xorstr("sv_accelerate_use_weapon_speed"));
	static auto sv_airaccelerate = g_CVar->FindVar(xorstr("sv_airaccelerate"));
	static auto sv_air_max_wishspeed = g_CVar->FindVar(xorstr("sv_air_max_wishspeed"));
	static auto sv_friction = g_CVar->FindVar(xorstr("sv_friction"));
	static auto sv_gravity = g_CVar->FindVar(xorstr("sv_gravity"));
	static auto sv_jump_impulse = g_CVar->FindVar(xorstr("sv_jump_impulse"));
	static auto sv_ladder_scale_speed = g_CVar->FindVar(xorstr("sv_ladder_scale_speed"));
	static auto sv_ledge_mantle_helper = g_CVar->FindVar(xorstr("sv_ledge_mantle_helper"));
	static auto sv_maxspeed = g_CVar->FindVar(xorstr("sv_maxspeed"));
	static auto sv_maxvelocity = g_CVar->FindVar(xorstr("sv_maxvelocity"));
	static auto sv_staminajumpcost = g_CVar->FindVar(xorstr("sv_staminajumpcost"));
	static auto sv_staminalandcost = g_CVar->FindVar(xorstr("sv_staminalandcost"));
	static auto sv_staminamax = g_CVar->FindVar(xorstr("sv_staminamax"));
	static auto sv_staminarecoveryrate = g_CVar->FindVar(xorstr("sv_staminarecoveryrate"));
	static auto sv_standable_normal = g_CVar->FindVar(xorstr("sv_standable_normal"));
	static auto sv_timebetweenducks = g_CVar->FindVar(xorstr("sv_timebetweenducks"));
	static auto sv_walkable_normal = g_CVar->FindVar(xorstr("sv_walkable_normal"));
	static auto sv_wateraccelerate = g_CVar->FindVar(xorstr("sv_wateraccelerate"));
	static auto sv_water_movespeed_multiplier = g_CVar->FindVar(xorstr("sv_water_movespeed_multiplier"));
	static auto sv_water_swim_mode = g_CVar->FindVar(xorstr("sv_water_swim_mode"));
	static auto sv_weapon_encumbrance_per_item = g_CVar->FindVar(xorstr("sv_weapon_encumbrance_per_item"));
	static auto sv_weapon_encumbrance_scale = g_CVar->FindVar(xorstr("sv_weapon_encumbrance_scale"));

	if (sv_accelerate->GetFloat() != 5.5f
		|| sv_accelerate_use_weapon_speed->GetFloat() != 1.0f
		|| sv_airaccelerate->GetFloat() != 12.0f
		|| sv_air_max_wishspeed->GetFloat() != 30.0f 
		|| sv_friction->GetFloat() != 5.2f 
		|| sv_gravity->GetFloat() != 800.0f
		|| sv_jump_impulse->GetFloat() != 301.993377f
		|| sv_ladder_scale_speed->GetFloat() != 0.78f
		|| sv_ledge_mantle_helper->GetFloat() != 1.00f 
		|| sv_maxspeed->GetFloat() != 320.0f 
		|| sv_maxvelocity->GetFloat() != 3500.0f
		|| sv_staminajumpcost->GetFloat() != 0.080f
		|| sv_staminalandcost->GetFloat() != 0.050f
		|| sv_staminamax->GetFloat() != 80.0f 
		|| sv_staminarecoveryrate->GetFloat() != 60.0f
		|| sv_standable_normal->GetFloat() != 0.7f
		|| sv_timebetweenducks->GetFloat() != 0.4f
		|| sv_walkable_normal->GetFloat() != 0.7f
		|| sv_wateraccelerate->GetFloat() != 10.0f
		|| sv_water_movespeed_multiplier->GetFloat() != 0.8f
		|| sv_water_swim_mode->GetFloat() != 0.0f
		|| sv_weapon_encumbrance_per_item->GetFloat() != 0.85f
		|| sv_weapon_encumbrance_scale->GetFloat() != 0.0f
		)
	{
		return;
	}

	if (csgo::local_player->flags() & FL_ONGROUND && cmd->buttons & IN_JUMP)
	{
		bhops += 1;
	}

	if (bhops == 1)
	{
		bhop = true;
	}
	else
	{
		bhop = false;
	}

	if (bhops > 1)
	{
		multibhop = true;
	}
	else
	{
		multibhop = false;
	}

	if (bhops >= 0 && g_GlobalVars->tickcount - saved_tick_count_air > 1)
	{
		bhops = 0;
	}

	bool land = false;

	Vector velocity = csgo::local_player->velocity();

	if (!(csgo::local_player->flags() & FL_ONGROUND))
	{
		saved_tick_count_air = g_GlobalVars->tickcount;
		dead_time_air = !(cmd->buttons & IN_MOVERIGHT) && !(cmd->buttons & IN_MOVELEFT) ? 1 : 0;

		if (cmd->mousedx < 5 && !strafe_right && !strafe_left)
		{
			strafe_right = true;
		}
		else if (cmd->mousedx > -5 && !strafe_right && !strafe_left)
		{
			strafe_left = true;
		}

		if (cmd->mousedx < 5 && !strafe_right && strafe_left)
		{
			strafe_right = true;
			strafe_left = false;
			strafes++;
		}
		else if (cmd->mousedx > -5 && strafe_right && !strafe_left) 
		{
			strafe_right = false;
			strafe_left = true;
			strafes++;
		}

		if (g_GlobalVars->tickcount != durationticks2)
		{
			durationticks = g_GlobalVars->tickcount - savedongroundtick;
			syncticks += round(velocity.Length2D()) > lastvelosynced ? 1 : 0;
			lastvelosynced = round(velocity.Length2D());
			durationticks2 = g_GlobalVars->tickcount;
		}


		max_velocity = float_max(max_velocity, round(velocity.Length2D()));

		height = float_max(height, csgo::local_player->origin().z - jumpposheight.z + 4.5999);

		if (!last_jumping)
		{
			jump_positions[0] = csgo::local_player->origin();

			pre_velocity = round(velocity.Length2D());
		}

		last_jumping = true;
	}

	if (csgo::local_player->flags() & FL_ONGROUND)
	{
		savedongroundtick = g_GlobalVars->tickcount;

		if (last_jumping)
		{
			land = true;
			jump_positions[1] = csgo::local_player->origin();
		}

		last_jumping = false;
	}

	if (!land)
	{
		return;
	}

	if (pre_velocity > 250 && pre_velocity < 253)
	{
		pre_velocity = 250;
	}

	if (jump_positions[1].z - jump_positions[0].z <= 64.f && jump_positions[1].z - jump_positions[0].z >= -8.f)
	{
		if (bhop && !multibhop)
		{
			height -= 3.2f;

			g_ChatElements->chat_printf(0, 0, std::string("").append("\x01").append(xorstr("bhop:")).append(std::to_string(pre_velocity) + xorstr("pre")).append(xorstr(" | ")).append(std::to_string(max_velocity) + xorstr("max")).append(xorstr(" | ")).append(std::to_string(height) + xorstr("height")).c_str());
		}
		else if (multibhop && !bhop)
		{
			height -= 3.5f;

		
			g_ChatElements->chat_printf(0, 0, std::string("").append("\x01").append(xorstr("mbh:")).append(std::to_string(pre_velocity) + xorstr("pre")).append(xorstr(" | ")).append(std::to_string(max_velocity) + xorstr("max")).append(xorstr(" | ")).append(std::to_string(height) + xorstr("height")).c_str());
		}
		else if (!bhop && !multibhop) 
		{
			height -= 4.6f;

			g_ChatElements->chat_printf(0, 0, std::string("").append("\x01").append(xorstr("lj:")).append(std::to_string(pre_velocity) + xorstr("pre")).append(xorstr(" | ")).append(std::to_string(max_velocity) + xorstr("max")).append(xorstr(" | ")).append(std::to_string(height) + xorstr("height")).c_str());
		}
	}
}

/*
void movement::autoedgebug(CUserCmd* cmd)
{
	if (!variables::config::movement::edgebug || !Utils::bind(variables::config::movement::edgebug_key, variables::config::movement::edgebug_key_type))
	{
		game->detectdata.detecttick = 0;
		game->detectdata.edgebugtick = 0;
		return;
	}

	if (!csgo::local_player || !csgo::local_player->is_alive() || !g_EngineClient->IsInGame() || !g_EngineClient->IsConnected())
	{
		game->detectdata.detecttick = 0;
		game->detectdata.edgebugtick = 0;
		return;
	}

	if (csgo::local_player->move_type() == MOVETYPE_LADDER || csgo::local_player->move_type() == MOVETYPE_NOCLIP || csgo::local_player->move_type() == MOVETYPE_OBSERVER)
	{
		game->detectdata.detecttick = 0;
		game->detectdata.edgebugtick = 0;
		return;
	}

	if (engine_prediction::get().data.m_fFlags & 1)
	{
		game->detectdata.detecttick = 0;
		game->detectdata.edgebugtick = 0;
		return;
	}

	if (g_GlobalVars->tickcount >= game->detectdata.detecttick && g_GlobalVars->tickcount <= game->detectdata.edgebugtick)
	{
		if (game->detectdata.crouched)
		{
			cmd->buttons |= IN_DUCK;
		}
		else
		{
			cmd->buttons &= ~IN_DUCK;
		}

		if (game->detectdata.strafing)
		{
			cmd->forwardmove = game->detectdata.forwardmove;
			cmd->sidemove = game->detectdata.sidemove;
			cmd->viewangles.y = math::normalizeyaw(game->detectdata.startingyaw + (game->detectdata.yawdelta * (g_GlobalVars->tickcount - game->detectdata.detecttick)));
			g_EngineClient->SetViewAngles();
		}
		else
		{
			cmd->forwardmove = 0.f;
			cmd->sidemove = 0.f;
		}


		return;
	}

	Vector originalpos = engine_prediction::get().data.m_vecOrigin;
	Vector originalvel = engine_prediction::get().data.m_vecVelocity;
	int originalflags = engine_prediction::get().data.m_fFlags;
	float originalfmove = cmd->forwardmove;
	float originalsmove = cmd->sidemove;
	Vector originalangles = cmd->viewangles;

	int ticklimit = TIME_TO_TICKS(variables::config::movement::edgebug_time);
	const float m_yaw = g_CVar->FindVar(xorstr("m_yaw"))->GetFloat();
	const float sensitivity = g_CVar->FindVar(xorstr("sensitivity"))->GetFloat();
	float yawdelta = std::clamp(cmd->mousedx * m_yaw * sensitivity, -30.f, 30.f);

		if (g_GlobalVars->tickcount < game->detectdata.detecttick || g_GlobalVars->tickcount > game->detectdata.edgebugtick)
		{
			const int desiredrounds = (variables::config::movement::edgebug_strafing && (yawdelta != 0.f) ? 4 : 2);

			const auto sv_gravity = g_CVar->FindVar(xorstr("sv_gravity"));
			float gv = sv_gravity->GetFloat();

			for (int predRound = 0; predRound < desiredrounds; predRound++)
			{
				restore_to_predicted_frame(g_Prediction->m_nCommandsPredicted() - 1);

				CUserCmd predictcmd = *cmd;

				game->detectdata.startingyaw = originalangles.y;

				if (predRound == 0)
				{
					game->detectdata.crouched = true;
					predictcmd.buttons |= IN_DUCK;
					game->detectdata.strafing = false;
					predictcmd.forwardmove = 0.f;
					predictcmd.sidemove = 0.f;

				}
				else if (predRound == 1)
				{
					game->detectdata.crouched = false;
					predictcmd.buttons &= ~IN_DUCK;
					game->detectdata.strafing = false;
					predictcmd.forwardmove = 0.f;
					predictcmd.sidemove = 0.f;

				}
				else if (predRound == 2)
				{
					game->detectdata.crouched = true;
					predictcmd.buttons |= IN_DUCK;
					game->detectdata.strafing = true;
					predictcmd.forwardmove = originalfmove;
					predictcmd.sidemove = originalsmove;
				}
				else if (predRound == 3)
				{
					game->detectdata.crouched = false;
					predictcmd.buttons &= ~IN_DUCK;
					game->detectdata.strafing = true;
					predictcmd.forwardmove = originalfmove;
					predictcmd.sidemove = originalsmove;
				}


				detectionpositions.clear();
				detectionpositions.push_back(std::pair<Vector, Vector>(game->local->origin(), game->local->velocity()));




				for (int ticksPredicted = 0; ticksPredicted < ticklimit; ticksPredicted++)
				{
					Vector old_velocity = game->local->velocity();
					int old_flags = game->local->flags();
					Vector old_pos = game->local->origin();

					if (game->detectdata.strafing)
					{
						predictcmd.viewangles.y = math::NormalizeYaw(originalangles.y + (yawdelta * ticksPredicted));
					}



					engine_prediction->start(&predictcmd); // predict 1 more tick
					Vector predicted_velocity = game->local->velocity();
					int predicted_flags = game->local->flags();
					detectionpositions.push_back(std::pair<Vector, Vector>(game->local->origin(), game->local->velocity()));
					engine_prediction->end();

					simple_cmd o;
					o.buttons = predictcmd.buttons;
					o.fmove = predictcmd.forwardmove;
					o.smove = predictcmd.sidemove;
					o.viewangles = predictcmd.viewangles.y;

					if ((old_flags & 1) || (predicted_flags & 1) || round(predicted_velocity.Length2D()) == 0.f || round(old_velocity.Length2D()) == 0.f || game->local->movetype() == MOVETYPE_LADDER || old_velocity.z > 0.f)
					{
						game->detectdata.detecttick = 0;
						game->detectdata.edgebugtick = 0;
						break;
					}

					if (detectionpositions.size() > 2)
					{
						if (egdebugdetection(detectionpositions.at(detectionpositions.size() - 3).second, detectionpositions.at(detectionpositions.size() - 2).second, detectionpositions.at(detectionpositions.size() - 1).second))
						{
							game->detectdata.detecttick = g_GlobalVars->tickcount;
							game->detectdata.edgebugtick = g_GlobalVars->tickcount + (ticksPredicted);
							game->detectdata.eblength = ticksPredicted;
							game->detectdata.forwardmove = originalfmove;
							game->detectdata.sidemove = originalsmove;
							game->detectdata.yawdelta = yawdelta;

							if (predRound < 2)
							{
								cmd->forwardmove = 0.f;
								cmd->sidemove = 0.f;
							}
							else
							{
								cmd->forwardmove = originalfmove;
								cmd->sidemove = originalsmove;
								cmd->viewangles.y = originalangles.y;
							}

							if (predRound == 0 || predRound == 2)
							{
								cmd->buttons |= IN_DUCK;
							}
							else
							{
								cmd->buttons &= ~IN_DUCK;
							}

							return;
						}

					}
				}
			}

		}
} */