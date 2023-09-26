#include "indicators.hpp"

color indicators::lerp(color a, color b, float t)
{
    return color(int(a.get_red() + t * (b.get_red() - a.get_red())), int(a.get_green() + t * (b.get_green() - a.get_green())), int(a.get_blue() + t * (b.get_blue() - a.get_blue())), int(a.get_alpha() + t * (b.get_alpha() - a.get_alpha())));
}

color indicators::huesaturationbrightnessalpha(float hue, float saturation, float brightness, float alpha)
{
    const float h = std::fmodf(hue, 1.0f) / (60.0f / 360.0f);
    const int i = static_cast<int>(h);
    const float f = h - static_cast<float>(i);
    const float p = brightness * (1.0f - saturation);
    const float q = brightness * (1.0f - saturation * f);
    const float t = brightness * (1.0f - saturation * (1.0f - f));

    float r = 0.0f, g = 0.0f, b = 0.0f;

    switch (i)
    {
    case 0:
        r = brightness, g = t, b = p;
        break;
    case 1:
        r = q, g = brightness, b = p;
        break;
    case 2:
        r = p, g = brightness, b = t;
        break;
    case 3:
        r = p, g = q, b = brightness;
        break;
    case 4:
        r = t, g = p, b = brightness;
        break;
    case 5:
    default:
        r = brightness, g = p, b = q;
        break;
    }

    return color(r, g, b, alpha);
}

void indicators::velocity()
{
    if (!variables::config::indicators::velocity)
    {
        return;
    }

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
    {
        return;
    }

    int width, height;
    g_EngineClient->GetScreenSize(width, height);

    int velocity = round(csgo::local_player->velocity().Length2D());

    auto velocity_color = [](int velocity) -> color
    {
        if (velocity > 0)
        {
            return color(variables::config::indicators::velocity_positive_clr[0], variables::config::indicators::velocity_positive_clr[1], variables::config::indicators::velocity_positive_clr[2]);
        }
        else if (velocity < 0)
        {
            return color(variables::config::indicators::velocity_negative_clr[0], variables::config::indicators::velocity_negative_clr[1], variables::config::indicators::velocity_negative_clr[2]);
        }
        else if (velocity > -1 && velocity < 1)
        {
            return color(variables::config::indicators::velocity_neutral_clr[0], variables::config::indicators::velocity_neutral_clr[1], variables::config::indicators::velocity_neutral_clr[2]);
        }
    };

    std::string velocity_str = std::to_string(velocity);
    std::string place_holder_velocity = "";

    last_delta_velocity = velocity - last_velocity;

    if (csgo::local_player->flags() & FL_ONGROUND)
    {
        if (didjumplast)
        {
            didjumplast = false;
        }

        place_holder_velocity = velocity_str;
    }
    else
    {
        if (!didjumplast)
        {
            pre_velocity = velocity;
            didjumplast = true;
        }

        if (variables::config::indicators::velocity_takeoff_on_ground)
        {
            place_holder_velocity = velocity_str + xorstr(" (") + std::to_string(pre_velocity) + xorstr(")");
        }
        else
        {
            place_holder_velocity = velocity_str;
        }
    }

    float time;

    if (velocity < variables::config::indicators::velocity_fade_strength)
    {
        time = 1.f * (float(velocity) / variables::config::indicators::velocity_fade_strength);
    }
    else
    {
        time = 1.f * float(velocity) / (float(velocity) * 0.5f);
    }

    imguirender::get().AddText(indicatorsfont, 29.0f, ImVec2(width / 2, (height / 2) + variables::config::indicators::indicator_position), place_holder_velocity, variables::config::indicators::velocity_style == 2 ? lerp(color(variables::config::indicators::velocity_from_clr[0], variables::config::indicators::velocity_from_clr[1], variables::config::indicators::velocity_from_clr[2], variables::config::indicators::velocity_from_clr[3]), color(variables::config::indicators::velocity_to_clr[0], variables::config::indicators::velocity_to_clr[1], variables::config::indicators::velocity_to_clr[2], variables::config::indicators::velocity_to_clr[3]), time) : variables::config::indicators::velocity_style == 1 ? huesaturationbrightnessalpha(1.f * (float(velocity) / variables::config::indicators::velocity_rainbow_hue), variables::config::indicators::velocity_rainbow_saturation, 1.0f, 1.0f) : velocity_color(last_delta_velocity), color(0, 0, 0), false, true, true, false);

    if (fabs(g_GlobalVars->tickcount - lasttick) > 5)
    {
        lasttick = g_GlobalVars->tickcount;
        last_velocity = velocity;
    }
}

void indicators::stamina()
{
    if (!variables::config::indicators::stamina)
    {
        return;
    }

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
    {
        return;
    }

    int width, height;
    g_EngineClient->GetScreenSize(width, height);

    static float last_speed = 0, last_jump_speed = 0;
    static float last_vel_update = 0.0f;
    float current_speed = csgo::local_player->stamina().Length2D();
    static bool last_onground = false;
    bool current_onground = csgo::local_player->flags() & FL_ONGROUND;

    if (last_onground && !current_onground)
    {
        last_jump_speed = current_speed;
    }

    std::string value_str;

    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << current_speed;
    value_str = ss.str();

    std::string str = value_str;

    std::stringstream ss1;
    ss1 << std::fixed << std::setprecision(1) << last_jump_speed;
    std::string value_str2 = ss1.str();
    last_delta_stamina = current_speed - last_speed;

    if (csgo::local_player->flags() & FL_ONGROUND || csgo::local_player->move_type() == MOVETYPE_LADDER)
    {
        str = value_str;
    }
    else if (variables::config::indicators::stamina_takeoff_on_ground && !(csgo::local_player->flags() & FL_ONGROUND))
    {
        str += " (" + value_str2 + ")";
    }

    if (variables::config::indicators::velocity)
    {
        imguirender::get().AddText(indicatorsfont, 29.0f, ImVec2(width / 2, (height / 2) + variables::config::indicators::indicator_position + 29), str, variables::config::indicators::stamina_style == 2 ? lerp(color(variables::config::indicators::stamina_from_clr[0], variables::config::indicators::stamina_from_clr[1], variables::config::indicators::stamina_from_clr[2], variables::config::indicators::stamina_from_clr[3]), color(variables::config::indicators::stamina_to_clr[0], variables::config::indicators::stamina_to_clr[1], variables::config::indicators::stamina_to_clr[2], variables::config::indicators::stamina_to_clr[3]), 1.f * (float(current_speed) / variables::config::indicators::velocity_fade_strength)) : variables::config::indicators::stamina_style == 1 ? huesaturationbrightnessalpha(1.f * (float(current_speed) / variables::config::indicators::stamina_rainbow_hue), variables::config::indicators::stamina_rainbow_saturation, 1.0f, 1.0f) : color(200, 200, 200, 255), color(0, 0, 0), false, true, true, false);
    }
    else
    {
        imguirender::get().AddText(indicatorsfont, 29.0f, ImVec2(width / 2, (height / 2) + variables::config::indicators::indicator_position), str, variables::config::indicators::stamina_style == 2 ? lerp(color(variables::config::indicators::stamina_from_clr[0], variables::config::indicators::stamina_from_clr[1], variables::config::indicators::stamina_from_clr[2], variables::config::indicators::stamina_from_clr[3]), color(variables::config::indicators::stamina_to_clr[0], variables::config::indicators::stamina_to_clr[1], variables::config::indicators::stamina_to_clr[2], variables::config::indicators::stamina_to_clr[3]), 1.f * (float(current_speed) / variables::config::indicators::velocity_fade_strength)) : variables::config::indicators::stamina_style == 1 ? huesaturationbrightnessalpha(1.f * (float(current_speed) / variables::config::indicators::stamina_rainbow_hue), variables::config::indicators::stamina_rainbow_saturation, 1.0f, 1.0f) : color(200, 200, 200, 255), color(0, 0, 0), false, true, true, false);
    }

    if (g_GlobalVars->curtime > last_vel_update)
    {
        last_speed = current_speed;
        last_vel_update = g_GlobalVars->curtime + 0.05f;
    }

    last_onground = current_onground;
}

void indicators::velocitygraph_gather_data()
{
    if (!variables::config::indicators::velocitygraph)
    {
        if (!velo_data.empty())
        {
            velo_data.clear();
        }


        return;
    }

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
    {
        if (!velo_data.empty()) 
        {
            velo_data.clear();
        }

        return;
    }

    if (velo_data.size() > 255)
    {
        velo_data.pop_back();
    }

    velocity_data_t current_data;

    current_data.speed = csgo::local_player->velocity().Length2D();
    current_data.on_ground = csgo::local_player->flags() & FL_ONGROUND;

    velo_data.insert(velo_data.begin(), current_data);
}

void indicators::velograph_draw()
{
    if (!variables::config::indicators::velocitygraph)
    {
        if (!velo_data.empty())
        {
            velo_data.clear();
        }


        return;
    }

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
    {
        if (!velo_data.empty())
        {
            velo_data.clear();
        }

        return;
    }

    if (velo_data.size() < 2) 
    {
        return;
    }

    int width, height;
    g_EngineClient->GetScreenSize(width, height);

    for (auto i = 0; i < velo_data.size() - 1; i++)
    {
        const auto current = velo_data[i];
        const auto next = velo_data[i + 1];

        const auto clamped_current_speed = std::clamp(current.speed, 0, 450);
        const auto clamped_next_speed = std::clamp(next.speed, 0, 450);

        const auto graph_pos = ImVec2(width / 2 + 255 * (variables::config::indicators::graph_scale / 2.f), (height / 2 + variables::config::indicators::indicator_position) - 30);

        float current_speed = (clamped_current_speed * 75 / 320);
        float next_speed = (clamped_next_speed * 75 / 320);

        float max_val = (int)velo_data.size() - 1;
        float val = (int)i;
        int alpha = fabs(max_val - fabs(val - max_val / 2) * 2.f);

        imguirender::get().AddLine(ImVec2(graph_pos.x - (i - 1) * variables::config::indicators::graph_scale, graph_pos.y - current_speed), ImVec2(graph_pos.x - i * variables::config::indicators::graph_scale, graph_pos.y - next_speed), color(255, 255, 255, alpha), 1.0f);
    }
}

void indicators::staminagraph_gather_data()
{
    if (!variables::config::indicators::staminagraph)
    {
        if (!stamina_data.empty())
        {
            stamina_data.clear();
        }

        return;
    }

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
    {
        if (!stamina_data.empty())
        {
            stamina_data.clear();
        }

        return;
    }

    if (stamina_data.size() > 255)
    {
        stamina_data.pop_back();
    }

    stamina_data_t current_data;

    current_data.stamina = csgo::local_player->stamina().Length2D();
    current_data.on_ground = csgo::local_player->flags() & FL_ONGROUND;

    stamina_data.insert(stamina_data.begin(), current_data);
}

void indicators::staminagraph_draw()
{
    if (!variables::config::indicators::staminagraph)
    {
        if (!stamina_data.empty())
        {
            stamina_data.clear();
        }

        return;
    }

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
    {
        if (!stamina_data.empty())
        {
            stamina_data.clear();
        }

        return;
    }

    if (stamina_data.size() < 2)
    {
        return;
    }

    int width, height;
    g_EngineClient->GetScreenSize(width, height);

    for (auto i = 0; i < stamina_data.size() - 1; i++)
    {
        const auto current = stamina_data[i];
        const auto next = stamina_data[i + 1];

        const auto clamped_current_speed = std::clamp(current.stamina, 0.0f, 35.0f);
        const auto clamped_next_speed = std::clamp(next.stamina, 0.0f, 35.0f);

        const auto graph_pos = ImVec2(width / 2 + 255 * (variables::config::indicators::graph_scale / 2.f), (height / 2 + variables::config::indicators::indicator_position) - 30);

        float current_speed = (clamped_current_speed * 25 / 35);
        float next_speed = (clamped_next_speed * 25 / 35);

        float max_val = (int)stamina_data.size() - 1;
        float val = (int)i;
        int alpha = fabs(max_val - fabs(val - max_val / 2) * 2.f);

        imguirender::get().AddLine(ImVec2(graph_pos.x - (i - 1) * variables::config::indicators::graph_scale, graph_pos.y - current_speed), ImVec2(graph_pos.x - i * variables::config::indicators::graph_scale, graph_pos.y - next_speed), color(166, 143, 242, alpha), 1.0f);
    }
} 

void indicators::add(std::string name, bool enabled, color clr)
{
    if (!m_indicators.count(name))
    {
        m_indicators.insert({ name,  { color(255, 255, 255, 0), 0} });
    }

    m_indicators[name].clr[0] = clr.get_red();
    m_indicators[name].clr[1] = clr.get_green();
    m_indicators[name].clr[2] = clr.get_blue();

    if (enabled)
    {
        if (m_indicators[name].alpha < 1.f)
        {
            m_indicators[name].alpha += g_GlobalVars->frametime * variables::config::indicators::speed;
        }

        if (m_indicators[name].alpha > 1.f)
        {
            m_indicators[name].alpha = 1.f;
        }
    }
    else
    {
        if (m_indicators[name].alpha > 0.f)
        {
            m_indicators[name].alpha -= g_GlobalVars->frametime * variables::config::indicators::speed;
        }

        if (m_indicators[name].alpha < 0.f)
        {
            m_indicators[name].alpha = 0.f;
        }
    }

    m_indicators[name].clr.set_alpha(255 * m_indicators[name].alpha);
}

void indicators::addindicators()
{
    if (!variables::config::indicators::indicators)
    {
        saved_tick_ej = 0;
        saved_tick_lj = 0;
        saved_tick_jb = 0;
        saved_tick_eb = 0;
        saved_tick_mj = 0;
        saved_tick_ag = 0;
        saved_tick_ps = 0;
        return;
    }
    
    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
    {
        saved_tick_ej = 0;
        saved_tick_lj = 0;
        saved_tick_jb = 0;
        saved_tick_eb = 0;
        saved_tick_mj = 0;
        saved_tick_ag = 0;
        saved_tick_ps = 0;
        return;
    }

    int width, height;
    g_EngineClient->GetScreenSize(width, height);

    if (movement::get().jbsuccesful)
    {
        saved_tick_jb = g_GlobalVars->tickcount;
    }

    if (movement::get().edgebug_should)
    {
        saved_tick_eb = g_GlobalVars->tickcount;
    }

    if (movement::get().mjsuccesful)
    {
        saved_tick_mj = g_GlobalVars->tickcount;
    }

    if (movement::get().ejsuccesful)
    {
        saved_tick_ej = g_GlobalVars->tickcount;
    }

    if (movement::get().ljsuccesful)
    {
        saved_tick_lj = g_GlobalVars->tickcount;
    }

    if (movement::get().pixelsurf_should || csgo::local_player->velocity().z == -6.25f)
    {
        saved_tick_ps = g_GlobalVars->tickcount;
    }

    if (movement::get().pixelsurf_should || csgo::local_player->velocity().z == -6.25f)
    {
        saved_tick_ag = g_GlobalVars->tickcount;
    }

    add("jb", variables::config::indicators::jumpbug && variables::config::movement::jumpbug && Utils::bind(variables::config::movement::jumpbug_key, variables::config::movement::jumpbug_key_type), g_GlobalVars->tickcount - saved_tick_jb < 25 ? color(191, 153, 232) : color(255, 255, 255));
    add("ej", variables::config::indicators::edgejump && variables::config::movement::edgejump && Utils::bind(variables::config::movement::edgejump_key, variables::config::movement::edgejump_key_type), g_GlobalVars->tickcount - saved_tick_ej < 15 ? color(variables::config::indicators::edgejump_detection_color[0], variables::config::indicators::edgejump_detection_color[1], variables::config::indicators::edgejump_detection_color[2]) : color(255, 255, 255, 255));
    add("lj", variables::config::indicators::longjump && variables::config::movement::longjump && Utils::bind(variables::config::movement::longjump_key, variables::config::movement::longjump_key_type), g_GlobalVars->tickcount - saved_tick_lj < 15 ? color(variables::config::indicators::longjump_detection_color[0], variables::config::indicators::longjump_detection_color[1], variables::config::indicators::longjump_detection_color[2]) : color(255, 255, 255, 255));
    add("eb", variables::config::indicators::edgebug && variables::config::movement::edgebug && Utils::bind(variables::config::movement::edgebug_key, variables::config::movement::edgebug_key_type), g_GlobalVars->tickcount - saved_tick_eb < 15 ? color(variables::config::indicators::edgebug_detection_color[0], variables::config::indicators::edgebug_detection_color[1], variables::config::indicators::edgebug_detection_color[2]) : color(255, 255, 255, 255));
    add("mj", variables::config::indicators::minijump && variables::config::movement::minijump && Utils::bind(variables::config::movement::minijump_key, variables::config::movement::minijump_key_type), g_GlobalVars->tickcount - saved_tick_mj < 15 ? color(variables::config::indicators::minijump_detection_color[0], variables::config::indicators::minijump_detection_color[1], variables::config::indicators::minijump_detection_color[2]) : color(255, 255, 255, 255));
    add("sh", variables::config::indicators::staminahop && variables::config::movement::staminahop && Utils::bind(variables::config::movement::staminahop_key, variables::config::movement::staminahop_key_type), g_GlobalVars->tickcount - saved_tick_mj < 15 ? color(variables::config::indicators::minijump_detection_color[0], variables::config::indicators::minijump_detection_color[1], variables::config::indicators::minijump_detection_color[2]) : color(255, 255, 255, 255));
    add("ag", variables::config::indicators::autoalign && variables::config::movement::autoalign && Utils::bind(variables::config::movement::autoalign_key, variables::config::movement::autoalign_key_type), g_GlobalVars->tickcount - saved_tick_ps < 15 ? color(variables::config::indicators::minijump_detection_color[0], variables::config::indicators::minijump_detection_color[1], variables::config::indicators::minijump_detection_color[2]) : color(255, 255, 255, 255));
    add("ps", variables::config::indicators::pixelsurf && variables::config::movement::pixelsurf && Utils::bind(variables::config::movement::pixelsurf_key, variables::config::movement::pixelsurf_key_type), g_GlobalVars->tickcount - saved_tick_ps < 15 ? color(variables::config::indicators::minijump_detection_color[0], variables::config::indicators::minijump_detection_color[1], variables::config::indicators::minijump_detection_color[2]) : color(255, 255, 255, 255));
    add("ad", variables::config::indicators::autoduck && variables::config::movement::autoduck && Utils::bind(variables::config::movement::autoduck_key, variables::config::movement::autoduck_key_type), g_GlobalVars->tickcount - saved_tick_mj < 15 ? color(variables::config::indicators::minijump_detection_color[0], variables::config::indicators::minijump_detection_color[1], variables::config::indicators::minijump_detection_color[2]) : color(255, 255, 255, 255));
    add("msl", variables::config::indicators::msl && variables::config::movement::msl && Utils::bind(variables::config::movement::msl_key, variables::config::movement::msl_key_type), g_GlobalVars->tickcount - saved_tick_mj < 15 ? color(variables::config::indicators::minijump_detection_color[0], variables::config::indicators::minijump_detection_color[1], variables::config::indicators::minijump_detection_color[2]) : color(255, 255, 255, 255));

    if (!variables::config::movement::jumpbug)
    {
        movement::get().jbsuccesful = 0;
    }

    if (!variables::config::movement::edgebug)
    {
        movement::get().edgebug_should = 0;
    }

    if (!variables::config::movement::minijump)
    {
        movement::get().mjsuccesful = 0;
    }

    if (!variables::config::movement::edgejump)
    {
        movement::get().ejsuccesful = 0;
    }

    if (!variables::config::movement::longjump)
    {
        movement::get().ljsuccesful = 0;
    }

    if (!variables::config::movement::pixelsurf)
    {
        movement::get().pssuccesful = 0;
    }

    if (!variables::config::movement::autoalign)
    {
        movement::get().agsuccesful = 0;
    }

    int position = 0;

    for (const auto& [name, data] : m_indicators)
    {
        if (data.alpha > 0.f)
        {
            if (variables::config::indicators::velocity || variables::config::indicators::stamina)
            {
                if (variables::config::indicators::velocity && variables::config::indicators::stamina)
                {
                    imguirender::get().AddText(indicatorsfont, 29.0f, ImVec2(width / 2, (height / 2) + variables::config::indicators::indicator_position + 58 + position), name, data.clr, color(0, 0, 0), false, true, true, false);
                }
                else
                {
                    imguirender::get().AddText(indicatorsfont, 29.0f, ImVec2(width / 2, (height / 2) + variables::config::indicators::indicator_position + 29 + position), name, data.clr, color(0, 0, 0), false, true, true, false);
                }
            }
            else
            {
                imguirender::get().AddText(indicatorsfont, 29.0f, ImVec2(width / 2, (height / 2) + variables::config::indicators::indicator_position + position), name, data.clr, color(0, 0, 0), false, true, true, false);
            }

            position += 29.0f + variables::config::indicators::sameline;
        }
    }
}
