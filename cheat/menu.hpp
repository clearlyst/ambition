#pragma once
#define NOMINMAX
#include <Windows.h>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <d3d9.h>
#include <basetsd.h>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_freetype.h"

#include "variables.hpp"
#include "helpers/xor.hpp"
#include "helpers/singleton.hpp"
#include "console debug/console.hpp"
#include "features/config system/config.hpp"
#include "features/notifications/notifications.hpp"

#include "valve_sdk/sdk.hpp"
#include "valve_sdk/csgostructs.hpp"

struct IDirect3DDevice9;

class menu : public singleton<menu>
{
public:
    void aimbot_page(ImVec2 base_first_child_position, ImVec2 first_case_child_short_lower_group_position, ImVec2 first_case_child_short_upper_group_size, ImVec2 first_case_child_long_group_size, ImVec2 first_case_short_lower_group_size, variables::config::aimbot::aimbot_value_t& aimbot_value, bool show_override_from_default);

    void triggerbot_page(ImVec2 base_first_child_position, ImVec2 first_case_child_short_lower_group_position, ImVec2 first_case_child_short_upper_group_size, ImVec2 first_case_child_long_group_size, ImVec2 first_case_short_lower_group_size, variables::config::triggerbot::triggerbot_value_t& triggerbot_value, bool show_override_from_default);

    void render();;
    void release();

    bool IsVisible() { return m_bIsVisible; };
    void SetVisible(bool bIsVisible) { m_bIsVisible = bIsVisible; };
private:
    bool m_bIsVisible = true;

    int tabs = 0;
    int subtab = 0;

    bool colorpicker(const char* label, color* v);
    bool checkbox(const char* name, bool* check);
    bool tab(const char* name, /*const char* icon,*/ bool select_check);
    bool button(const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags);
    bool exslider(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags);
    bool sliderint(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags);
    bool sliderfloat(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags);
    bool keybind(const char* label, int* k, int* key_style);
};