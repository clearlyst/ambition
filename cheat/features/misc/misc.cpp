#include "misc.hpp"
#include <TlHelp32.h>
#include <Windows.h>

void misc::spectatorlist()
{
    if (!variables::config::misc::spectatorlist)
    {
        return;
    }

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame())
    {
        return;
    }

    std::string spectators;
    
    for (int i = 0; i < g_GlobalVars->maxClients; i++)
    {
        player_t* entity = player_t::GetPlayerByIndex(i);

        if (!entity || entity->is_alive() || entity->IsDormant())
        {
            continue;
        }

        auto target = (player_t*)entity->observer_target();

        if (!target || target != csgo::local_player)
        {
            continue;
        }

        if (entity == target)
        {
            continue;
        }

        player_info_t spectating_info;
        g_EngineClient->GetPlayerInfo(entity->EntIndex(), &spectating_info);

        if (spectating_info.ishltv)
        {
            continue;
        }

        std::string mode;

        switch (entity->obsserver_mode())
        {
        case OBS_MODE_IN_EYE:
            mode = "first person";
            break;
        case OBS_MODE_CHASE:
            mode = "3rd person";
            break;
        case OBS_MODE_ROAMING:
            mode = "noclip";
            break;
        case OBS_MODE_DEATHCAM:
            mode = "deathcam";
            break;
        case OBS_MODE_FREEZECAM:
            mode = "freezecam";
            break;
        case OBS_MODE_FIXED:
            mode = "fixed";
            break;
        default:
            mode = "";
            break;
        }

        if (variables::config::misc::spectatorlist_mode)
        {
            spectators += spectating_info.fakeplayer ? xorstr("[bot] ") + std::string(spectating_info.szName) + xorstr(" | ") + mode + u8"\n" : std::string(spectating_info.szName) + xorstr(" | ") + mode + u8"\n";
        }
        else
        {
            spectators += spectating_info.fakeplayer ? xorstr("[bot] ") + std::string(spectating_info.szName) + u8"\n" : std::string(spectating_info.szName) + u8"\n";
        }
    }

    imguirender::get().AddText(screenmiscfont, 12.0f, ImVec2(5, 5), spectators, color(255, 255, 255, 255), color(0, 0, 0), false, true);
}

void misc::watermark()
{
    if (!variables::config::misc::watermark)
    {
        return;
    }

    int width, height;
    g_EngineClient->GetScreenSize(width, height);

    static float current_time = 0.f;
    static int last_fps = (int)(1.0f / g_GlobalVars->frametime);

    if (current_time > 0.5f)
    {
        last_fps = (int)(1.0f / g_GlobalVars->frametime);
        current_time = 0.f;
    }

    current_time += g_GlobalVars->frametime;

    std::string text = xorstr("ambition | ") + std::to_string(last_fps) + xorstr(" fps");

    imguirender::get().AddText(screenmiscfont, 12.0f, ImVec2(width - 5, 5), text, color(255, 255, 255, 255), color(0, 0, 0), false, true, false, true);
}

std::wstring ttl = L"";
DWORD procID = 0;

bool is_spotify(const PROCESSENTRY32W& entry)
{
    return std::wstring(entry.szExeFile) == L"Spotify.exe";
}

BOOL __stdcall enum_windows_proc(HWND hwnd, LPARAM lParam)
{
    const auto& pids = *reinterpret_cast<std::vector<DWORD>*>(lParam);

    DWORD winId;
    GetWindowThreadProcessId(hwnd, &winId);

    if (pids.empty())
        return FALSE;

    for (DWORD pid : pids)
    {
        if (winId == pid)
        {
            std::wstring title(GetWindowTextLength(hwnd) + 1, L'\0');
            GetWindowTextW(hwnd, &title[0], title.size());

            if (wcsstr(title.c_str(), L"GDI+ Window (Spotify.exe)") || wcsstr(title.c_str(), L"Default IME") || title.empty() || wcsstr(title.c_str(), L"MSCTFIME UI"))
            {
                continue;
            }

            if (lstrlenW(title.c_str()) > 1)
            {
               procID = pid;
               ttl = title;
            }
        }
    }

    return TRUE;
}

bool handle_spotify_window()
{
    std::vector<DWORD> pids;

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32W entry;
    entry.dwSize = sizeof(entry);

    if (!Process32FirstW(snap, &entry))
    {
        return false;
    }

    do
    {
        if (is_spotify(entry))
        {
            pids.emplace_back(entry.th32ProcessID);
        }
    } while (Process32NextW(snap, &entry));

    return EnumWindows(enum_windows_proc, reinterpret_cast<LPARAM>(&pids));
}

void misc::spotifymusic()
{
    if (!variables::config::misc::spotify)
    {
        return;
    }

    if (g_GlobalVars->realtime > lasttime + 2.f)
    {
        if (handle_spotify_window())
        {
            std::string ttl2;

            if (char title[128]; WideCharToMultiByte(CP_UTF8, 0, ttl.c_str(), -1, title, 128, nullptr, nullptr))
            {
                ttl2 = std::string(title);
            }

            spotifytitle = wcsstr(ttl.c_str(), L"spotify") ? xorstr("stopped / not playing") : "" + ttl2;

            if (strstr(spotifytitle.c_str(), "Spotify Premium"))
            {
                spotifytitle = xorstr("stopped / not playing");
            }

            if (strstr(spotifytitle.c_str(), "Advertisement"))
            {
                spotifytitle = xorstr("advertisement");
            }
        }
        else
        {
            spotifytitle = xorstr("spotify not open");
        }

        lasttime = g_GlobalVars->realtime;
    }

    int x, y;
    g_EngineClient->GetScreenSize(x, y);

    if (spotifytitle.length() > 32)
    {
        spotifytitle = spotifytitle.substr(0, 32).append(xorstr("..."));
    }

    if (variables::config::misc::watermark)
    {
        imguirender::get().AddText(screenmiscfont, 12.0f, ImVec2(x - 5, 20), spotifytitle, color(255, 255, 255, 255), color(0, 0, 0), false, true, false, true);
    }
    else
    {
       imguirender::get().AddText(screenmiscfont, 12.0f, ImVec2(x - 5, 5), spotifytitle, color(255, 255, 255, 255), color(0, 0, 0), false, true, false, true);
    }
}

void misc::changeviewmodeloffsets()
{
    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
    {
        return;
    }

    static auto old_view_model_x = g_CVar->FindVar(xorstr("viewmodel_offset_x"))->GetFloat();
    static auto old_view_model_y = g_CVar->FindVar(xorstr("viewmodel_offset_y"))->GetFloat();
    static auto old_view_model_z = g_CVar->FindVar(xorstr("viewmodel_offset_z"))->GetFloat();

    g_CVar->FindVar(xorstr("viewmodel_offset_x"))->m_fnChangeCallbacks.clear();
    g_CVar->FindVar(xorstr("viewmodel_offset_y"))->m_fnChangeCallbacks.clear();
    g_CVar->FindVar(xorstr("viewmodel_offset_z"))->m_fnChangeCallbacks.clear();

    if (variables::config::misc::changeviewmodeloffsets)
    {
        g_CVar->FindVar(xorstr("viewmodel_offset_x"))->SetValue(variables::config::misc::viewmodeloffset_x);
        g_CVar->FindVar(xorstr("viewmodel_offset_y"))->SetValue(variables::config::misc::viewmodeloffset_y);
        g_CVar->FindVar(xorstr("viewmodel_offset_z"))->SetValue(variables::config::misc::viewmodeloffset_z);
    }
    else
    {
        g_CVar->FindVar(xorstr("viewmodel_offset_x"))->SetValue(old_view_model_x);
        g_CVar->FindVar(xorstr("viewmodel_offset_y"))->SetValue(old_view_model_y);
        g_CVar->FindVar(xorstr("viewmodel_offset_z"))->SetValue(old_view_model_z);
    }
}

void misc::changeviewmodelfov()
{
    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
    {
        return;
    }

    static auto old_view_model_fov = g_CVar->FindVar(xorstr("viewmodel_fov"))->GetFloat();

    g_CVar->FindVar(xorstr("viewmodel_fov"))->m_fnChangeCallbacks.clear();

    if (variables::config::misc::changeviewmodelfov)
    {
        g_CVar->FindVar(xorstr("viewmodel_fov"))->SetValue(variables::config::misc::viewmodelfov);
    }
    else
    {
        g_CVar->FindVar(xorstr("viewmodel_fov"))->SetValue(old_view_model_fov);
    }
}

void misc::changeweaponswayscale()
{
    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
    {
        return;
    }

    static auto cl_wpn_sway_scale = g_CVar->FindVar(xorstr("cl_wpn_sway_scale"))->GetFloat();

    g_CVar->FindVar(xorstr("cl_wpn_sway_scale"))->m_fnChangeCallbacks.clear();

    if (variables::config::misc::changeweaponswayscale)
    {
        g_CVar->FindVar(xorstr("cl_wpn_sway_scale"))->SetValue(variables::config::misc::weaponswayscale);
    }
    else
    {
        g_CVar->FindVar(xorstr("cl_wpn_sway_scale"))->SetValue(cl_wpn_sway_scale);
    }
}

void misc::forcecrosshair()
{
    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
    {
        return;
    }

    static auto weapon_debug_spread_show = g_CVar->FindVar(xorstr("weapon_debug_spread_show"))->GetFloat();

    g_CVar->FindVar(xorstr("weapon_debug_spread_show"))->m_fnChangeCallbacks.clear();

    if (variables::config::misc::forcecrosshair && !csgo::local_player->is_scoped())
    {
        variables::config::misc::snipercrosshair = false;
        g_CVar->FindVar(xorstr("weapon_debug_spread_show"))->SetValue(3);
    }
    else
    {
        g_CVar->FindVar(xorstr("weapon_debug_spread_show"))->SetValue(weapon_debug_spread_show);
    }
}

void misc::recoilcrosshair()
{
    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
    {
        return;
    }

    static auto cl_crosshair_recoil = g_CVar->FindVar(xorstr("cl_crosshair_recoil"))->GetFloat();

    g_CVar->FindVar(xorstr("cl_crosshair_recoil"))->m_fnChangeCallbacks.clear();

    if (variables::config::misc::recoilcrosshair)
    {
        g_CVar->FindVar(xorstr("cl_crosshair_recoil"))->SetValue(1);
    }
    else
    {
        g_CVar->FindVar(xorstr("cl_crosshair_recoil"))->SetValue(cl_crosshair_recoil);
    }
}

void misc::snipercrosshair()
{
    if (!variables::config::misc::snipercrosshair || !g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive() || csgo::local_player->is_scoped())
    {
        return;
    }

    int width, height;
    g_EngineClient->GetScreenSize(width, height);

    auto weapon = csgo::local_player->active_weapon();

    if (!weapon)
    {
        return;
    }

    auto weapon_data = weapon->get_weapon_data();

    if (!weapon_data)
    {
        return;
    }

    if (!weapon->issniper())
    {
        return;
    }

    imguirender::get().AddRectFilled(ImVec2(width / 2, height / 2), ImVec2(width / 2 + 2, height / 2 + 2), color(255, 255, 255, 255));
}

void misc::rankreavel(CUserCmd* cmd)
{
    if (!variables::config::misc::rankreveal || !g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player)
    {
        return;
    }

    if (cmd->buttons & IN_SCORE)
    {
        g_CHLClient->DispatchUserMessage(CS_UM_ServerRankRevealAll, 0, 0, nullptr);
    }
}

void misc::usespammer(CUserCmd* cmd)
{
    if (!variables::config::misc::usekeyspam || !GetAsyncKeyState(0x45))
    {
        return;
    }

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player || !csgo::local_player->is_alive())
    {
        return;
    }

    if (csgo::local_player->active_weapon()->get_weapon_data()->m_iWeaponType != WEAPONTYPE_C4)
    {
        if (cmd->command_number % 2)
        {
            cmd->buttons |= IN_USE;
        }
        else
        {
            cmd->buttons &= ~IN_USE;
        }
    }
}

void misc::regionchanger()
{
    if (!variables::config::misc::regionchanger)
    {
        return;
    }

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame() || !csgo::local_player)  
    {
        return;
    }

    const std::string dataCentersList[] = { "syd", "vie", "gru", "scl", "dxb", "par", "fra", "hkg",
    "maa", "bom", "tyo", "lux", "ams", "limc", "man", "waw", "sgp", "jnb",
    "mad", "sto", "lhr", "atl", "eat", "ord", "lax", "mwh", "okc", "sea", "iad" };

    static std::string* force_relay_cluster_value = *(std::string**)(Utils::PatternScan2(xorstr("steamnetworkingsockets.dll"), xorstr("B8 ? ? ? ? B9 ? ? ? ? 0F 43")) + 1);

    *force_relay_cluster_value = dataCentersList[variables::config::misc::regionchanger_type];
}

void misc::removeflash()
{
    if (!variables::config::misc::removeflash)
    {
        return;
    }

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame())
    {
        return;
    }

    csgo::local_player->flash_alpha() = 255.0f - variables::config::misc::removeflash_time * 2.55f;
}

void misc::removesmoke()
{
    if (!variables::config::misc::removewireframesmoke || !variables::config::misc::removefullsmoke)
    {
        return;
    }

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame())
    {
        return;
    }

    std::vector<const char*> smoke_materials =
    {
        xorstr("particle/vistasmokev1/vistasmokev1_fire"),
        xorstr("particle/vistasmokev1/vistasmokev1_smokegrenade"),
        xorstr("particle/vistasmokev1/vistasmokev1_emods"),
        xorstr("particle/vistasmokev1/vistasmokev1_emods_impactdust"),
    };

    for (auto materials : smoke_materials)
    {
        IMaterial* get_smoke_material = g_MatSystem->FindMaterial(materials, TEXTURE_GROUP_OTHER);

        get_smoke_material->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, variables::config::misc::removewireframesmoke);
        get_smoke_material->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, variables::config::misc::removefullsmoke);
    }
}

void misc::removefire()
{
    if (!variables::config::misc::removewireframefire || !variables::config::misc::removefullfire)
    {
        return;
    }

    if (!g_EngineClient->IsConnected() || !g_EngineClient->IsInGame())
    {
        return;
    }

    std::vector<const char*> fire_materials =
    {
        xorstr("particle/fire_burning_character/fire_env_fire"),
        xorstr("particle/fire_burning_character/fire_env_fire_depthblend"),
        xorstr("particle/fire_burning_character/fire_burning_character_depthblend"),
        xorstr("particle/fire_burning_character/fire_burning_character"),
        xorstr("particle/fire_burning_character/fire_burning_character_nodepth"),
        xorstr("particle/particle_flares/particle_flare_001"),
        xorstr("particle/particle_flares/particle_flare_004"),
        xorstr("particle/particle_flares/particle_flare_004b_mod_ob"),
        xorstr("particle/particle_flares/particle_flare_004b_mod_z"),
        xorstr("particle/fire_explosion_1/fire_explosion_1_bright"),
        xorstr("particle/fire_explosion_1/fire_explosion_1b"),
        xorstr("particle/fire_particle_4/fire_particle_4"),
        xorstr("particle/fire_explosion_1/fire_explosion_1_oriented")
    };

    for (auto materials : fire_materials)
    {
        IMaterial* get_fire_material = g_MatSystem->FindMaterial(materials, TEXTURE_GROUP_OTHER);

        get_fire_material->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, variables::config::misc::removewireframefire);
        get_fire_material->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, variables::config::misc::removefullfire);
    }
}