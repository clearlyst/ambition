#include "esp.hpp"

RECT get_box(entity_t* ent, Vector pointstransf[])
{
	RECT rect{};
	auto collideable = ent->GetCollideable();

	if (!collideable)
		return rect;

	auto min = collideable->OBBMins();
	auto max = collideable->OBBMaxs();

	const matrix3x4_t& trans = ent->coordinate_frame();

	Vector points[] =
	{
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector pointsTransformed[8];

	for (int i = 0; i < 8; i++)
	{
		math::vector_transform(points[i], trans, pointsTransformed[i]);
	}

	Vector screen_points[8] = {};

	for (int i = 0; i < 8; i++)
	{
		if (!math::world_to_screen(pointsTransformed[i], screen_points[i]))
			return rect;
	}

	auto left = screen_points[0].x;
	auto top = screen_points[0].y;
	auto right = screen_points[0].x;
	auto bottom = screen_points[0].y;

	for (int i = 1; i < 8; i++)
	{
		if (left > screen_points[i].x)
			left = screen_points[i].x;
		if (top < screen_points[i].y)
			top = screen_points[i].y;
		if (right < screen_points[i].x)
			right = screen_points[i].x;
		if (bottom > screen_points[i].y)
			bottom = screen_points[i].y;
	}

	return RECT{ (long)left, (long)top, (long)right, (long)bottom };
}

void esp::run()
{
	if (!variables::config::esp::enable)
	{
		return;
	}

	if (!Utils::bind(variables::config::esp::key, variables::config::esp::key_type))
	{
		return;
	}

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame())
    {
        return;
    }

	const float delta_time = (1.f / variables::config::esp::fadeinout_time) * g_GlobalVars->frametime;

    for (auto i = 1; i < g_GlobalVars->maxClients; i++)
    {
		player_t* entity = player_t::GetPlayerByIndex(i);

		if (!entity || !entity->is_player() || entity == csgo::local_player)
		{
			continue;
		}

		const int index = entity->EntIndex();

		if (variables::config::esp::fadeinout)
		{
			entity->IsDormant() || !entity->is_alive() ? this->player_alpha[index] -= delta_time : this->player_alpha[index] += delta_time;

			this->player_alpha[index] = std::clamp(this->player_alpha[index], 0.f, 1.f);

			if (this->player_alpha[index] < 0.1f)
			{
				continue;
			}
		}
		else
		{
			if (!entity->is_alive() || entity->IsDormant())
			{
				continue;
			}
		}

		if (entity->team() == csgo::local_player->team() && !variables::config::esp::teammates)
		{
			continue;
		}

		if (variables::config::esp::engine_radar) 
		{ 
			entity->spotted() = true;
		}

		visible = csgo::local_player->can_see_player_pos(entity, entity->get_eye_pos());

		Vector head = entity->get_hitbox_position(HITBOX_HEAD);

	    Vector origin = entity->origin();

		color clr = visible ? color(variables::config::esp::visible_clr[0], variables::config::esp::visible_clr[1], variables::config::esp::visible_clr[2], variables::config::esp::visible_clr[3]) : color(variables::config::esp::occluded_clr[0], variables::config::esp::occluded_clr[1], variables::config::esp::occluded_clr[2], variables::config::esp::occluded_clr[3]);
		color fade_clr = visible ? color(variables::config::esp::visible_clr[0], variables::config::esp::visible_clr[1], variables::config::esp::visible_clr[2], int(this->player_alpha[index] * variables::config::esp::visible_clr[3])) : color(variables::config::esp::occluded_clr[0], variables::config::esp::occluded_clr[1], variables::config::esp::occluded_clr[2], int(this->player_alpha[index] * variables::config::esp::occluded_clr[3]));

		color outline = visible ? color(0, 0, 0, variables::config::esp::visible_clr[3]) : color(0, 0, 0, variables::config::esp::occluded_clr[3]);
		color fade_outline = visible ? color(0, 0, 0, int(this->player_alpha[index] * variables::config::esp::visible_clr[3])) : color(0, 0, 0, int(this->player_alpha[index] * variables::config::esp::occluded_clr[3]));

		if (math::world_to_screen(head, pl_head) || math::world_to_screen(origin, pl_origin))
		{
			Vector points_transformed[8];

			bbox = get_box(entity, points_transformed);

			std::swap(bbox.top, bbox.bottom);

			if (variables::config::esp::box)
			{
				box(entity, variables::config::esp::fadeinout ? fade_clr : clr, variables::config::esp::fadeinout ? fade_outline : outline);
			}
			
			if (variables::config::esp::name)
			{
				name(entity, variables::config::esp::fadeinout ? fade_clr : clr);
			}
			
			if (variables::config::esp::health || variables::config::esp::weapon || variables::config::esp::weapon_icon || variables::config::esp::ammo || variables::config::esp::ammo_bar)
			{
				bottom_bar(entity, variables::config::esp::fadeinout ? fade_clr : clr);
			}
			
			if (variables::config::esp::flags)
			{
				flags(entity, variables::config::esp::fadeinout ? fade_clr : clr);
			}

			if (variables::config::esp::health_bar)
			{
				healthbar(entity, clr, outline);
			}

			if (variables::config::esp::skeleton)
			{
				skeleton(entity, variables::config::esp::fadeinout ? fade_clr : clr);
			}

			if (variables::config::esp::viewangle)
			{
				viewangle(entity, variables::config::esp::fadeinout ? fade_clr : clr);
			}

			if (variables::config::esp::headbox)
			{
				head_box(entity, variables::config::esp::fadeinout ? fade_clr : clr);
			}

			if (variables::config::esp::snapline)
			{
				snapline(entity, variables::config::esp::fadeinout ? fade_clr : clr);
			}

			if (variables::config::esp::dlight)
			{
				dlight(entity, variables::config::esp::fadeinout ? fade_clr : clr);
			}
		}

		if (variables::config::esp::outofview)
		{
			outofview(entity, variables::config::esp::fadeinout ? fade_clr : clr);
		}
    }

	for (auto i = 1; i < g_EntityList->GetHighestEntityIndex(); i++)
	{
		entity_t* entity = reinterpret_cast<entity_t*>(g_EntityList->GetClientEntity(i));

		if (!entity || entity->is_player() || entity->IsDormant())
		{
			continue;
		}

		if (variables::config::esp::droppedweapon || variables::config::esp::droppedweapon_icon)
		{
			dropped_weapon(entity);
		}

		if (variables::config::esp::throwngrenade || variables::config::esp::throwngrenade_icon)
		{
			throwed_grenade(entity);
		}
	}
}

void esp::box(player_t* target, color clr, color outline)
{
	if (variables::config::esp::box_rect)
	{
		if (variables::config::esp::box_outline)
		{
			imguirender::get().AddRect(ImVec2(bbox.left - 1, bbox.top - 1), ImVec2(bbox.right + 1, bbox.bottom + 1), outline);
		}

		if (variables::config::esp::box_inline)
		{
			imguirender::get().AddRect(ImVec2(bbox.left + 1, bbox.top + 1), ImVec2(bbox.right - 1, bbox.bottom - 1), outline);
		}

		imguirender::get().AddRect(ImVec2(bbox.left, bbox.top), ImVec2(bbox.right, bbox.bottom), clr, 0.0f, ImDrawCornerFlags_None);
	}
}

void esp::name(player_t* target, color clr)
{
	player_info_t player_info;
	g_EngineClient->GetPlayerInfo(target->EntIndex(), &player_info);

	std::string name = player_info.szName;
	std::string text = player_info.fakeplayer ? xorstr("[bot] ") + name : name;

	imguirender::get().AddText(firstespfont, 12.0f, ImVec2(bbox.left + (bbox.right - bbox.left) / 2, bbox.top - 14.0f), text, clr, color(0, 0, 0), true, false, true, false);
}

void esp::bottom_bar(player_t* target, color clr)
{
	auto offset_bottom = 0;

	auto weapon = target->active_weapon();

	if (!weapon)
	{
		return;
	}

	auto weapon_data = weapon->get_weapon_data();

	if (!weapon_data)
	{
		return;
	}

	int get_health = target->health();
	int get_distance = csgo::local_player->origin().DistTo(target->origin()) * 0.0254f;
	int get_current_ammo = weapon->clip1_count();
	int get_max_ammo = weapon_data->m_iMaxClip1;

	int v89 = std::min(100, get_health);

	int red = 0x50;
	int green = 0xFF;
	int blue = 0x50;

	if (v89 >= 25)
	{
		if (v89 <= 50)
		{
			red = 0xD7;
			green = 0xC8;
			blue = 0x50;
		}
	}
	else
	{
		red = 0xFF;
		green = 0x32;
		blue = 0x50;
	}

	std::string health = std::to_string(get_health);
	std::string health_text = variables::config::esp::health_hide_suffix ? health : health + xorstr(" hp");
	std::string distance = std::to_string(get_distance);
	std::string distance_text = distance + xorstr(" m");
	std::string currentammo_text = std::to_string(get_current_ammo);
	std::string maxammo_text = std::to_string(get_max_ammo);

	if (variables::config::esp::ammo_bar)
	{
		if (weapon->isgun())
		{
			float box_w = (float)fabs(bbox.right - bbox.left);

			int width = ((box_w * get_current_ammo) / get_max_ammo);

			variables::config::esp::ammo_bar_background ? imguirender::get().AddRectFilled(ImVec2(bbox.left, bbox.bottom + 3), ImVec2(bbox.right, bbox.bottom + 6 + variables::config::esp::ammo_bar_size), color(0, 0, 0, 200)) : imguirender::get().AddRect(ImVec2(bbox.left, bbox.bottom + 3), ImVec2(bbox.right, bbox.bottom + 6 + variables::config::esp::ammo_bar_size), color(0, 0, 0, 200));

			imguirender::get().AddRectFilled(ImVec2(bbox.left + 1, bbox.bottom + 4), ImVec2(bbox.left + width - 1, bbox.bottom + 5 + variables::config::esp::ammo_bar_size), clr);

			offset_bottom += 7 + variables::config::esp::ammo_bar_size;
		}
	}

	if (variables::config::esp::health)
	{
		imguirender::get().AddText(secondespfont, 12.0f, ImVec2(bbox.left + (bbox.right - bbox.left) / 2, bbox.bottom + offset_bottom), health_text, variables::config::esp::health_rgb ? color(red, green, 0, 255) : clr, color(0, 0, 0), true, false, true, false);
		
	    offset_bottom += 12;
    }

	if (variables::config::esp::weapon_icon)
	{
		imguirender::get().AddText(weaponiconfont, 12.0f, ImVec2(bbox.left + (bbox.right - bbox.left) / 2, bbox.bottom + offset_bottom), weapon->weapon_icons(), clr, color(0, 0, 0), true, false, true, false);

		offset_bottom += 12;
	}

	if (variables::config::esp::weapon)
	{
		imguirender::get().AddText(secondespfont, 12.0f, ImVec2(bbox.left + (bbox.right - bbox.left) / 2, bbox.bottom + offset_bottom), weapon->weapon_name(), clr, color(0, 0, 0), true, false, true, false);

		offset_bottom += 12;
	}

	if (variables::config::esp::ammo)
	{
		if (weapon->isgun())
		{
			imguirender::get().AddText(secondespfont, 12.0f, ImVec2(bbox.left + (bbox.right - bbox.left) / 2, bbox.bottom + offset_bottom), xorstr("[") + currentammo_text + xorstr("|") + maxammo_text + xorstr("]"), clr, color(0, 0, 0), true, false, true, false);

			offset_bottom += 12;
		}
	}

	if (variables::config::esp::distance)
	{
		imguirender::get().AddText(secondespfont, 12.0f, ImVec2(bbox.left + (bbox.right - bbox.left) / 2, bbox.bottom + offset_bottom), distance_text, clr, color(0, 0, 0), false, true, true, false);
	}
}

void esp::flags(player_t* target, color clr)
{
	std::vector<std::pair<std::string, color>> flags;

	if (variables::config::esp::armour && target->armor() > 0)
	{
		flags.push_back({ target->has_helmet() ? xorstr("hk") : xorstr("k"), clr });
	}

	if (variables::config::esp::balance)
	{
		flags.push_back({ std::string(xorstr("$")).append(std::to_string(target->money())), clr });
	}

	if (variables::config::esp::flashed && target->is_flashed())
	{
		flags.push_back({ xorstr("flashed"), clr });
	}

	if (variables::config::esp::scoped && target->is_scoped())
	{
		flags.push_back({ xorstr("scoped"), clr });
	}

	//if (variables::config::esp::reloading)
	//{
	//	flags.push_back({ xorstr("reloading..."), clr });
	//}

	if (variables::config::esp::defusing && target->is_defusing())
	{
		flags.push_back({ xorstr("defusing..."), clr });
	}

	if (variables::config::esp::rescuing && target->is_rescuing())
	{
		flags.push_back({ xorstr("rescuing..."), clr });
	}

	auto position = 0;

	for (auto text : flags) 
	{
		imguirender::get().AddText(secondespfont, 12.0f, ImVec2(bbox.right + 3, bbox.top + position), text.first, text.second, color(0, 0, 0), true, false);

		position += 12;
	}
}

void esp::healthbar(player_t* target, color clr, color outline)
{
	float box_h = (float)fabs(bbox.bottom - bbox.top);
	int height = (box_h * target->health()) / 100;
	int v89 = std::min(100, target->health());

	int red = 0x50;
	int green = 0xFF;
	int blue = 0x50;

	if (v89 >= 25)
	{
		if (v89 <= 50)
		{
			red = 0xD7;
			green = 0xC8;
			blue = 0x50;
		}
	}
	else
	{
		red = 0xFF;
		green = 0x32;
		blue = 0x50;
	}

	variables::config::esp::health_bar_background ? imguirender::get().AddRectFilled(ImVec2(bbox.left - 6 - variables::config::esp::health_bar_size, bbox.top), ImVec2(bbox.left - 3, bbox.bottom), outline) : imguirender::get().AddRect(ImVec2(bbox.left - 6 - variables::config::esp::health_bar_size, bbox.top), ImVec2(bbox.left - 3, bbox.bottom), outline);

	imguirender::get().AddRectFilled(ImVec2(bbox.left - 5 - variables::config::esp::health_bar_size, bbox.bottom - height + 1), ImVec2(bbox.left - 4, bbox.bottom - 1), variables::config::esp::health_rgb ? color(red, green, 0, 255) : clr);
}

void esp::skeleton(player_t* target, color clr)
{
	auto p_studio_hdr = g_MdlInfo->GetStudiomodel(target->GetModel());

	if (!p_studio_hdr)
	{ 
		return;
	}

	for (int i = 0; i < p_studio_hdr->num_bones; i++)
	{
		mstudiobone_t* bone = p_studio_hdr->GetBone(i);

		if (!bone) 
		{ 
			return;
		}

		if (bone && (bone->flags & BONE_USED_BY_HITBOX) && (bone->parent != -1))
		{
			Vector child = target->get_bone_position(i);
			Vector parent = target->get_bone_position(bone->parent);
			Vector start, end;

			// Render skeleton
			if (math::world_to_screen(parent, start) && math::world_to_screen(child, end))
			{
				imguirender::get().AddLine(ImVec2(start.x, start.y), ImVec2(end.x, end.y), clr, variables::config::esp::skeleton_thickness);
			}
		}
	}
}

void esp::outofview(player_t* target, color clr)
{
	if (visible && !variables::config::esp::outofview_occluded)
	{
		return;
	}

	Vector viewangles;
	g_EngineClient->GetViewAngles(viewangles);

	int x, y;
	g_EngineClient->GetScreenSize(x, y);

	const auto center = ImVec2(x / 2.f, y / 2.f);

	const auto& rotate = DEG2RAD(viewangles.y - math::calculate_angle(csgo::local_player->origin() + csgo::local_player->view_offset(), target->origin()).y - 90.f);

	const auto radius = 50 + variables::config::esp::outofview_distance;
	const auto size = variables::config::esp::outofview_size;

	auto pos = ImVec2(center.x + radius * cosf(rotate) * (2 * (0.5f + 10 * 0.5f * 0.01f)), center.y + radius * sinf(rotate));
	auto line = pos - center;

	auto arrowBase = pos - (line * (size / (2 * (tanf(M_PI / 4) / 2) * Vector2D { line.x, line.y }.Length())));
	auto normal = ImVec2(-line.y, line.x);
	auto left = arrowBase + normal * (size / (2 * Vector2D{ line.x, line.y }.Length()));
	auto right = arrowBase + normal * (-size / (2 * Vector2D{ line.x, line.y }.Length()));

	imguirender::get().AddTriangleFilled(ImVec2(left.x, left.y), ImVec2(right.x, right.y), ImVec2(pos.x, pos.y), clr);
}

void esp::snapline(player_t* target, color clr)
{
	int width, height;
	g_EngineClient->GetScreenSize(width, height);

	if (variables::config::esp::snapline_bottom)
	{
		imguirender::get().AddLine(ImVec2((bbox.right + bbox.left) / 2, bbox.bottom), ImVec2(width / 2.f, height), clr, variables::config::esp::snapline_thickness);
	}

	if (variables::config::esp::snapline_center)
	{
		imguirender::get().AddLine(ImVec2((bbox.right + bbox.left) / 2, (bbox.top + bbox.bottom) / 2), ImVec2(width / 2.f, height / 2.f), clr, variables::config::esp::snapline_thickness);
	}

	if (variables::config::esp::snapline_upper)
	{
		imguirender::get().AddLine(ImVec2((bbox.right + bbox.left) / 2, bbox.top), ImVec2(width / 2.f, 0), clr, variables::config::esp::snapline_thickness);
	}
}

void esp::viewangle(player_t* target, color clr)
{
	Vector src;
	Vector pos = target->get_bone_position(8);
	math::angle_vectors(target->eye_angles(), src);
	src *= variables::config::esp::viewangle_distance;
	Vector dst = pos + src;
	Vector start, end;

	if (math::world_to_screen(pos, start) && math::world_to_screen(dst, end))
	{
		imguirender::get().AddLine(ImVec2(start.x, start.y), ImVec2(end.x, end.y), clr, variables::config::esp::viewangle_thickness);
	}
}

void esp::head_box(player_t* player, color clr)
{
	Vector head_pos;

	if (math::world_to_screen(player->get_bone_position(8), head_pos))
	{
		variables::config::esp::headbox_filled ? imguirender::get().AddRectFilled(ImVec2(head_pos.x - 2, head_pos.y - 2), ImVec2(head_pos.x + 2, head_pos.y + 2), clr) : imguirender::get().AddRect(ImVec2(head_pos.x - 2, head_pos.y - 2), ImVec2(head_pos.x + 2, head_pos.y + 2), clr, 1.0f);
	}
}

void esp::dlight(player_t* target, color clr)
{
	if (!visible)
	{
		return;
	}

	Vector origin = target->origin();
	dlight_t* dlight = g_Effects->cl_alloc_dlight(target->EntIndex());
	dlight->color.r = clr.get_red();
	dlight->color.g = clr.get_green();
	dlight->color.b = clr.get_blue();
	dlight->color.exponent = 5.f;
	dlight->direction = origin;
	dlight->origin = origin;
	dlight->radius = variables::config::esp::dlight_radius;
	dlight->die_time = g_GlobalVars->curtime + 0.1f;
	dlight->decay = dlight->radius / 2.f;
	dlight->key = target->EntIndex();
}

void esp::throwed_grenade(entity_t* entity)
{
	auto client_class = entity->GetClientClass();

	if (!client_class)
	{
		return;
	}

	auto model = entity->GetModel();

	if (!model)
	{
		return;
	}

	auto studio_model = g_MdlInfo->GetStudiomodel(model);

	if (!studio_model)
	{
		return;
	}

	auto name = (std::string)studio_model->name;

	if (strstr(client_class->m_pNetworkName, "Projectile"))
	{
		if (!strstr(studio_model->name, "thrown") && !strstr(studio_model->name, "dropped"))
		{
			return;
		}

		Vector grenade_origin = entity->origin();
		Vector grenade_position;

		if (!math::world_to_screen(grenade_origin, grenade_position))
		{
			return;
		}

		imguirender::get().AddText(secondespfont, 12.0f, ImVec2(grenade_position.x, grenade_position.y - 13), xorstr("thrown"), color(255, 255, 255, 200), color(0, 0, 0), false, true, true, false);

	    std::string grenade_name;
		std::string grenade_icon;

		if (name.find("flashbang") != std::string::npos)
		{
			grenade_name = xorstr("flashbang");
			grenade_icon = xorstr("i");
		}

		if (name.find("smokegrenade") != std::string::npos)
		{
			grenade_name = xorstr("smoke");
			grenade_icon = xorstr("k");
		}

		if (name.find("incendiarygrenade") != std::string::npos)
		{
			grenade_name = xorstr("incgrenade");
			grenade_icon = xorstr("n");
		}

		if (name.find("molotov") != std::string::npos)
		{
			grenade_name = xorstr("molotov");
			grenade_icon = xorstr("l");
		}

		if (name.find("fraggrenade") != std::string::npos)
		{
			grenade_name = xorstr("he grenade");
			grenade_icon = xorstr("j");
		}

		if (name.find("decoy") != std::string::npos)
		{
			grenade_name = xorstr("decoy");
			grenade_icon = xorstr("m");
		}

		auto offset = 0;

		if (variables::config::esp::throwngrenade_icon)
		{
			imguirender::get().AddText(weaponiconfont, 12.0f, ImVec2(grenade_position.x, grenade_position.y), grenade_icon, color(255, 255, 255, 200), color(0, 0, 0), false, true, true, false);
			offset += 13;
		}

		if (variables::config::esp::throwngrenade)
		{
			imguirender::get().AddText(secondespfont, 12.0f, ImVec2(grenade_position.x, grenade_position.y + offset), grenade_name, color(255, 255, 255, 200), color(0, 0, 0), false, true, true, false);
		}
	}
}

void esp::dropped_weapon(entity_t* entity)
{
	auto weapon = (weapon_t*)entity;

	auto is_weapon = weapon->is_weapon();

	if (!is_weapon)
	{
		return;
	}

	auto weapon_data = weapon->get_weapon_data();

	if (!weapon_data)
	{
		return;
	}

	auto current = weapon->clip1_count();
	auto max = weapon_data->m_iMaxClip1;

	Vector droppedweapon_origin = weapon->origin();
	Vector droppedweapon_position;

	if (droppedweapon_origin.x == 0.f && droppedweapon_origin.y == 0.f && droppedweapon_origin.z == 0.f)
	{
		return;
	}

	if (!math::world_to_screen(droppedweapon_origin, droppedweapon_position))
	{
		return;
	}

	if (droppedweapon_position.x == 0.f && droppedweapon_position.y == 0.f && droppedweapon_position.z == 0.f)
	{
		return;
	}

	std::string droppedweapon_name = weapon->weapon_name();
	std::string droppedweapon_icon = weapon->weapon_icons();
	std::string currentammo_text = std::to_string(current);
	std::string maxammo_text = std::to_string(max);

	auto offset = 0;

	if (variables::config::esp::droppedweapon_icon)
	{
		imguirender::get().AddText(weaponiconfont, 12.0f, ImVec2(droppedweapon_position.x, droppedweapon_position.y), droppedweapon_icon, color(255, 255, 255, 200), color(0, 0, 0), false, true, true, false);

		offset += 13;
	}

	if (variables::config::esp::droppedweapon)
	{
		imguirender::get().AddText(secondespfont, 12.0f, ImVec2(droppedweapon_position.x, droppedweapon_position.y + offset), droppedweapon_name, color(255, 255, 255, 200), color(0, 0, 0), false, true, true, false);

		offset += 13;
	}

	if (variables::config::esp::droppedweapon_ammo)
	{
		imguirender::get().AddText(secondespfont, 12.0f, ImVec2(droppedweapon_position.x, droppedweapon_position.y + offset), xorstr("[") + currentammo_text + xorstr("|") + maxammo_text + xorstr("]"), color(255, 255, 255, 200), color(0, 0, 0), false, true, true, false);
	}
}