#include "menu.hpp"

#define ICON_FA_CROSSHAIRS xorstr("\xef\x81\x9b")
#define ICON_FA_EYE xorstr("\xef\x81\xae")
#define ICON_FA_USER xorstr("\xef\x80\x87")     
#define ICON_FA_GEAR xorstr("\xef\x80\x93")
#define ICON_FA_FOLDER xorstr("\xef\x81\xbb")
#define ICON_FA_CODE xorstr("\xef\x84\xa1")
#define ICON_FA_FONT xorstr("\xef\x80\xb1")
#define ICON_FA_TRASH xorstr("\xef\x87\xb8")
#define ICON_FA_INBOX xorstr("\xef\x80\x9c")
#define ICON_FA_MAP_MARKED xorstr("\xef\x96\x9f")
#define ICON_FA_MONKEY xorstr("\xef\x9b\xbb")
#define ICON_FA_MOON_STARS xorstr("\xef\x9d\x95")
#define ICON_FA_PAINT_BRUSH xorstr("\xef\x87\xbc")
#define ICON_FA_PALLET_ALT xorstr("\xef\x92\x83")

const char* const KeyNames[] =
{
    "[unknown]",
    "[m1]",
    "[m2]",
    "[cancel]",
    "[m3]",
    "[m4]",
    "[m5]",
    "[unknown]",
    "[back]",
    "[tab]",
    "[unknown]",
    "[unknown]",
    "[clear]",
    "[return]",
    "[unknown]",
    "[unknown]",
    "[shift]",
    "[control]",
    "[alt]",
    "[pause]",
    "[caps]",
    "[kana]",
    "[unknown]",
    "[junja]",
    "[final]",
    "[kanji]",
    "[unknown]",
    "[escape]",
    "[convert]",
    "[nonconvert]",
    "[accept]",
    "[modechange]",
    "[space]",
    "[prior]",
    "[next]",
    "[end]",
    "[home]",
    "[left]",
    "[up]",
    "[right]",
    "[down]",
    "[select]",
    "[print]",
    "[execute]",
    "[snapshot]",
    "[insert]",
    "[delete]",
    "[help]",
    "[0]",
    "[1]",
    "[2]",
    "[3]",
    "[4]",
    "[5]",
    "[6]",
    "[7]",
    "[8]",
    "[9]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[a]",
    "[b]",
    "[c]",
    "[d]",
    "[e]",
    "[f]",
    "[g]",
    "[h]",
    "[i]",
    "[j]",
    "[k]",
    "[l]",
    "[m]",
    "[n]",
    "[o]",
    "[p]",
    "[q]",
    "[r]",
    "[s]",
    "[t]",
    "[u]",
    "[v]",
    "[w]",
    "[x]",
    "[y]",
    "[z]",
    "[left win]",
    "[right win]",
    "[apps]",
    "[unknown]",
    "[sleep]",
    "[num0]",
    "[num1]",
    "[num2]",
    "[num3]",
    "[num4]",
    "[num5]",
    "[num6]",
    "[num7]",
    "[num8]",
    "[num9]",
    "[multiply]",
    "[add]",
    "[separate]",
    "[subtract]",
    "[decimal]",
    "[divide]",
    "[f1]",
    "[f2]",
    "[f3]",
    "[f4]",
    "[f5]",
    "[f6]",
    "[f7]",
    "[f8]",
    "[f9]",
    "[f10]",
    "[f11]",
    "[f12]",
    "[f13]",
    "[f14]",
    "[f14]",
    "[f16]",
    "[f17]",
    "[f18]",
    "[f19]",
    "[f20]",
    "[f21]",
    "[f22]",
    "[f23]",
    "[f24]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[numlock]",
    "[scroll]",
    "[equal]",
    "[masshou]",
    "[touroku]",
    "[loya]",
    "[roya]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[unknown]",
    "[left shift]",
    "[right shift]",
    "[left control]",
    "[right control]",
    "[left alt]",
    "[right alt]"
};

void menu::aimbot_page(ImVec2 base_first_child_position, ImVec2 first_case_child_short_lower_group_position, ImVec2 first_case_child_short_upper_group_size, ImVec2 first_case_child_long_group_size, ImVec2 first_case_short_lower_group_size, variables::config::aimbot::aimbot_value_t& aimbot_value, bool show_override_from_default = false)
{
    ImGui::SetCursorPos(base_first_child_position);
    ImGui::BeginChild("general", first_case_child_short_upper_group_size, false, ImGuiWindowFlags_None);
    {
        const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

        ImGui::PushFont(textmenufont);

        ImGui::Combo(xorstr("select weapon"), &menu::get().subtab, xorstr("general\0pistols\0heavy pistols\0smgs\0shotguns\0rifles\0snipers\0"));
        checkbox(xorstr("enable aimbot"), &variables::config::aimbot::enable); if (!variables::config::aimbot::shootataimkey) { ImGui::SameLine(group_w - 60); keybind(xorstr("aimbot key"), &variables::config::aimbot::key, &variables::config::aimbot::key_type); }
        checkbox(xorstr("working on fire key"), &variables::config::aimbot::shootataimkey);
        if (show_override_from_default)
        {
            checkbox(xorstr("override general"), &aimbot_value.override_general);
        }
        if (show_override_from_default && aimbot_value.override_general)
        {
            checkbox(xorstr("auto pistol"), &aimbot_value.autopistol);
            checkbox(xorstr("silent"), &aimbot_value.silent);
            checkbox(xorstr("backtrack"), &aimbot_value.backtrack);
        }
        else if (!show_override_from_default)
        {
            checkbox(xorstr("auto pistol"), &aimbot_value.autopistol);
            checkbox(xorstr("silent"), &aimbot_value.silent);
            checkbox(xorstr("backtrack"), &aimbot_value.backtrack);
        }

        ImGui::PopFont();
    }
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("settings", first_case_child_long_group_size, false, ImGuiWindowFlags_None);
    {
        const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

        ImGui::PushFont(textmenufont);

        if (show_override_from_default && aimbot_value.override_general)
        {
            if (ImGui::BeginCombo(xorstr("hitbox"), xorstr("select"), ImGuiComboFlags_NoArrowButton))
            {
                ImGui::Selectable(xorstr("head"), &aimbot_value.head, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("neck"), &aimbot_value.neck, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("chest"), &aimbot_value.chest, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("stomach"), &aimbot_value.stomach, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("pelvis"), &aimbot_value.pelvis, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("foot"), &aimbot_value.foot, ImGuiSelectableFlags_DontClosePopups);

                ImGui::EndCombo();
            }
            ImGui::Combo(xorstr("priority type"), &aimbot_value.priority, xorstr("fov\0distance\0health\0"));
            sliderfloat(xorstr("field of view"), &aimbot_value.fov, 0.0f, 360.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            sliderfloat(xorstr("smooth"), &aimbot_value.smooth, 0.0f, 120.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            checkbox(xorstr("compensate recoil"), &aimbot_value.compensaterecoil);
            if (aimbot_value.autowall)
            {
                sliderint(xorstr("min damage"), &aimbot_value.mindamage, 0, 100, "%d", ImGuiSliderFlags_AlwaysClamp);
            }
        }
        else if (!show_override_from_default)
        {
            if (ImGui::BeginCombo(xorstr("hitbox"), xorstr("select"), ImGuiComboFlags_NoArrowButton))
            {
                ImGui::Selectable(xorstr("head"), &aimbot_value.head, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("neck"), &aimbot_value.neck, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("chest"), &aimbot_value.chest, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("stomach"), &aimbot_value.stomach, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("pelvis"), &aimbot_value.pelvis, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("foot"), &aimbot_value.foot, ImGuiSelectableFlags_DontClosePopups);

                ImGui::EndCombo();
            }
            ImGui::Combo(xorstr("priority type"), &aimbot_value.priority, xorstr("fov\0distance\0health\0"));
            sliderfloat(xorstr("field of view"), &aimbot_value.fov, 0.0f, 360.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            sliderfloat(xorstr("smooth"), &aimbot_value.smooth, 0.0f, 120.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            checkbox(xorstr("compensate recoil"), &aimbot_value.compensaterecoil);
            if (aimbot_value.autowall)
            {
                sliderint(xorstr("min damage"), &aimbot_value.mindamage, 0, 100, "%d", ImGuiSliderFlags_AlwaysClamp);
            }
        }

        ImGui::PopFont();
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(first_case_child_short_lower_group_position);
    ImGui::BeginChild("filters", first_case_short_lower_group_size, false, ImGuiWindowFlags_None);
    {
        const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

        ImGui::PushFont(textmenufont);

        if (show_override_from_default && aimbot_value.override_general)
        {
            checkbox(xorstr("flash check"), &aimbot_value.flashcheck);
            checkbox(xorstr("smoke check"), &aimbot_value.smokecheck);
            checkbox(xorstr("enemy in air check"), &aimbot_value.enemyinair);
            checkbox(xorstr("self in air check"), &aimbot_value.selfinair);
            checkbox(xorstr("aim through walls"), &aimbot_value.autowall);
            checkbox(xorstr("aim at backtrack"), &aimbot_value.backtrack);
        }
        else if (!show_override_from_default)
        {
            checkbox(xorstr("flash check"), &aimbot_value.flashcheck);
            checkbox(xorstr("smoke check"), &aimbot_value.smokecheck);
            checkbox(xorstr("enemy in air check"), &aimbot_value.enemyinair);
            checkbox(xorstr("self in air check"), &aimbot_value.selfinair);
            checkbox(xorstr("aim through walls"), &aimbot_value.autowall);
            checkbox(xorstr("aim at teammates"), &aimbot_value.teammates);
            checkbox(xorstr("aim at backtrack"), &aimbot_value.aimatbacktrack);
        }

        ImGui::PopFont();
    }
    ImGui::EndChild();
}

void menu::triggerbot_page(ImVec2 base_first_child_position, ImVec2 first_case_child_short_lower_group_position, ImVec2 first_case_child_short_upper_group_size, ImVec2 first_case_child_long_group_size, ImVec2 first_case_short_lower_group_size, variables::config::triggerbot::triggerbot_value_t& triggerbot_value, bool show_override_from_default = false)
{
    ImGui::SetCursorPos(base_first_child_position);
    ImGui::BeginChild("general", first_case_child_short_upper_group_size, false, ImGuiWindowFlags_None);
    {
        const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

        ImGui::PushFont(textmenufont);

        ImGui::Combo(xorstr("select weapon"), &menu::get().subtab, xorstr("general\0pistols\0heavy pistols\0smgs\0shotguns\0rifles\0snipers\0"));
        checkbox(xorstr("enable aimbot"), &variables::config::triggerbot::enable); ImGui::SameLine(group_w - 60); keybind(xorstr("triggerbot key"), &variables::config::triggerbot::key, &variables::config::aimbot::key_type); 
        if (show_override_from_default)
        {
            checkbox(xorstr("override general"), &triggerbot_value.override_general);
        }
        if (show_override_from_default && triggerbot_value.override_general)
        {
            checkbox(xorstr("auto pistol"), &triggerbot_value.autopistol);
        }
        else if (!show_override_from_default)
        {
            checkbox(xorstr("auto pistol"), &triggerbot_value.autopistol);
        }

        ImGui::PopFont();
    }
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("settings", first_case_child_long_group_size, false, ImGuiWindowFlags_None);
    {
        const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

        ImGui::PushFont(textmenufont);

        if (show_override_from_default && triggerbot_value.override_general)
        {
            if (ImGui::BeginCombo(xorstr("hitbox"), xorstr("select"), ImGuiComboFlags_NoArrowButton))
            {
                ImGui::Selectable(xorstr("head"), &triggerbot_value.head, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("neck"), &triggerbot_value.neck, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("chest"), &triggerbot_value.chest, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("stomach"), &triggerbot_value.stomach, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("foot"), &triggerbot_value.foot, ImGuiSelectableFlags_DontClosePopups);

                ImGui::EndCombo();
            }
        }
        else if (!show_override_from_default)
        {
            if (ImGui::BeginCombo(xorstr("hitbox"), xorstr("select"), ImGuiComboFlags_NoArrowButton))
            {
                ImGui::Selectable(xorstr("head"), &triggerbot_value.head, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("neck"), &triggerbot_value.neck, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("chest"), &triggerbot_value.chest, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("stomach"), &triggerbot_value.stomach, ImGuiSelectableFlags_DontClosePopups);
                ImGui::Selectable(xorstr("foot"), &triggerbot_value.foot, ImGuiSelectableFlags_DontClosePopups);

                ImGui::EndCombo();
            }
        }

        ImGui::PopFont();
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(first_case_child_short_lower_group_position);
    ImGui::BeginChild("filters", first_case_short_lower_group_size, false, ImGuiWindowFlags_None);
    {
        const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

        ImGui::PushFont(textmenufont);

        if (show_override_from_default && triggerbot_value.override_general)
        {
            checkbox(xorstr("flash check"), &triggerbot_value.flashcheck);
            checkbox(xorstr("smoke check"), &triggerbot_value.smokecheck);
            checkbox(xorstr("enemy in air check"), &triggerbot_value.enemyinair);
            checkbox(xorstr("self in air check"), &triggerbot_value.selfinair);
            checkbox(xorstr("aim at teammates"), &triggerbot_value.teammates);
        }
        else if (!show_override_from_default)
        {
            checkbox(xorstr("flash check"), &triggerbot_value.flashcheck);
            checkbox(xorstr("smoke check"), &triggerbot_value.smokecheck);
            checkbox(xorstr("enemy in air check"), &triggerbot_value.enemyinair);
            checkbox(xorstr("self in air check"), &triggerbot_value.selfinair);
            checkbox(xorstr("aim at teammates"), &triggerbot_value.teammates);
        }

        ImGui::PopFont();
    }
    ImGui::EndChild();
}

void menu::render()
{
    if (!this->IsVisible())
    {
        return;
    }

    ImGuiStyle* style = &ImGui::GetStyle();

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TextDisabled, ImVec4(0.784f, 0.784f, 0.784f, 0.784f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.10f, 0.08f, 0.11f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.10f, 0.13f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.10f, 0.08f, 0.11f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.13f, 0.11f, 0.15f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.15f, 0.12f, 0.16f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.16f, 0.14f, 0.18f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.16f, 0.14f, 0.18f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.16f, 0.14f, 0.18f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.16f, 0.14f, 0.18f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.13f, 0.11f, 0.15f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(0.13f, 0.11f, 0.15f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, ImVec4(0.16f, 0.14f, 0.18f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive, ImVec4(0.349f, 0.267f, 0.434f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.349f, 0.267f, 0.434f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.217f, 0.188f, 0.247f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.349f, 0.267f, 0.434f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.217f, 0.188f, 0.247f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.251f, 0.220f, 0.282f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.349f, 0.267f, 0.434f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.217f, 0.188f, 0.247f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.251f, 0.220f, 0.282f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.349f, 0.267f, 0.434f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.217f, 0.188f, 0.247f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_SeparatorHovered, ImVec4(0.251f, 0.220f, 0.282f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_SeparatorActive, ImVec4(0.349f, 0.267f, 0.434f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ResizeGrip, ImVec4(0.217f, 0.188f, 0.247f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, ImVec4(0.251f, 0.220f, 0.282f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, ImVec4(0.349f, 0.267f, 0.434f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.217f, 0.188f, 0.247f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TabHovered, ImVec4(0.251f, 0.220f, 0.282f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4(0.349f, 0.267f, 0.434f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TabSelected, ImVec4(0.349f, 0.267f, 0.434f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 12.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));
    
    style->WindowMenuButtonPosition = ImGuiDir_None;
    style->FramePadding = ImVec2(5, 5);
    style->FrameBorderSize = 0.0f;
    style->FrameRounding = 12.0f;
    style->PopupRounding = 12.0f;
    style->PopupBorderSize = 0.0f;
    style->ScrollbarRounding = 12.0f;
    style->ScrollbarSize = 12.0f;
    style->GrabMinSize = 20.0f;
    style->GrabRounding = 12.f;
    style->ChildBorderSize = 0.0f;
    style->ChildRounding = 12.0f;
    style->SeparatorTextBorderSize = 1.0f;
    style->SeparatorTextAlign = ImVec2(0.5f, 0.5f);
    style->SeparatorTextPadding = ImVec2(20, 5);
    style->CellPadding = ImVec2(5, 5);
    style->ItemSpacing = ImVec2(5, 5);
    style->ItemInnerSpacing = ImVec2(5, 5);
    style->TouchExtraPadding = ImVec2(5, 5);
    style->IndentSpacing = 5.0f;
    style->LogSliderDeadzone = 0; 

    ImGui::PushFont(titlemenufont);
    ImGui::SetNextWindowSize(ImVec2(830, 670));
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Once);
    ImGui::Begin("ambition / alpha build", NULL, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    {
        const ImVec2 pos = ImGui::GetWindowPos();
        const float width = ImGui::GetWindowWidth();
        const float height = ImGui::GetWindowHeight();

        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x, pos.y + 25), ImVec2(pos.x + width, pos.y + 55), ImColor(0.13f, 0.11f, 0.15f, 1.0f), 0.0f, 0);

        ImGui::SetCursorPos(ImVec2(width * 0.5f - 180, 30));
        if (tab("aimbot", tabs == 0))
        {
            tabs = 0;
        }

        ImGui::SameLine();
        if (tab("triggerbot", tabs == 1))
        {
            tabs = 1;
        }

        ImGui::SameLine();
        if (tab("esp", tabs == 2))
        {
            tabs = 2;
        }

        ImGui::SameLine();
        if (tab("visual", tabs == 3))
        {
            tabs = 3;
        }

        ImGui::SameLine();
        if (tab("misc", tabs == 4))
        {
            tabs = 4;
        }

        ImGui::SameLine();
        if (tab("movement", tabs == 5))
        {
            tabs = 5;
        }

        ImGui::SameLine();
        if (tab("skins", tabs == 6))
        {
            tabs = 6;
        }

        ImGui::SameLine();
        if (tab("settings", tabs == 7))
        {
            tabs = 7;
        }

        static int size1 = 422;
        static int size2 = 373;
        static int pos1 = 100;
        static int pos2 = 100;


        /* GENERAL */

        const auto base_first_child_position = ImVec2(5, 60);

        /* FIRST CASE */

        const auto first_case_child_short_lower_group_position = ImVec2(5, height - 315);

        const auto first_case_child_short_upper_group_size = ImVec2(415, height - 380);
        const auto first_case_child_long_group_size = ImVec2(width - 430, height - 65);
        const auto first_case_short_lower_group_size = ImVec2(415, height - 360);
        const auto first_child_short_lower_group_size = ImVec2(415, height - 340);

        /* SECOND CASE */
 
        const auto second_case_child_group_size = ImVec2(width - 423, height - 373);

        /* THIRD CASE */

        const auto third_case_child_group_size = ImVec2(width - 423, height - 65);

        switch (tabs)
        {
        case 0:
            if (subtab == 0)
            {
                aimbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::aimbot::general);
            }

            if (subtab == 1)
            {
                aimbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::aimbot::pistols, true);
            }

            if (subtab == 2)
            {
                aimbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::aimbot::heavy_pistols, true);
            }

            if (subtab == 3)
            {
                aimbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::aimbot::smg, true);
            }

            if (subtab == 4)
            {
                aimbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::aimbot::shotguns, true);
            }

            if (subtab == 5)
            {
                aimbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::aimbot::rifles, true);
            }

            if (subtab == 6)
            {
                aimbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::aimbot::snipers, true);
            }
            break;
        case 1:
            if (subtab == 0)
            {
                triggerbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::triggerbot::general);
            }

            if (subtab == 1)
            {
                triggerbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::triggerbot::pistols, true);
            }

            if (subtab == 2)
            {
                triggerbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::triggerbot::heavy_pistols, true);
            }

            if (subtab == 3)
            {
                triggerbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::triggerbot::smg, true);
            }

            if (subtab == 4)
            {
                triggerbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::triggerbot::shotguns, true);
            }

            if (subtab == 5)
            {
                triggerbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::triggerbot::rifles, true);
            }

            if (subtab == 6)
            {
                triggerbot_page(base_first_child_position, first_case_child_short_lower_group_position, first_case_child_short_upper_group_size, first_case_child_long_group_size, first_case_short_lower_group_size, variables::config::triggerbot::snipers, true);
            }
            break;
        case 2:
            ImGui::SetCursorPos(base_first_child_position);
            ImGui::BeginChild("general", third_case_child_group_size, false, ImGuiWindowFlags_None);
            {
                const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::PushFont(textmenufont);
                checkbox(xorstr("enable esp"), &variables::config::esp::enable); ImGui::SameLine(); colorpicker(xorstr("visible esp colour"), &variables::config::esp::visible_clr); ImGui::SameLine(); colorpicker(xorstr("ocludded esp colour"), &variables::config::esp::occluded_clr); ImGui::SameLine(); keybind(xorstr("paint key"), &variables::config::esp::key, &variables::config::esp::key_type);
                if (variables::config::esp::enable)
                {
                    checkbox(xorstr("engine radar"), &variables::config::esp::engine_radar);
                    checkbox(xorstr("paint on teammates"), &variables::config::esp::teammates);
                    checkbox(xorstr("paint fade in/out"), &variables::config::esp::fadeinout);
                    checkbox(xorstr("paint box"), &variables::config::esp::box);
                    checkbox(xorstr("paint head box"), &variables::config::esp::headbox);
                    checkbox(xorstr("paint name"), &variables::config::esp::name);
                    checkbox(xorstr("paint weapon"), &variables::config::esp::weapon);
                    checkbox(xorstr("paint weapon icon"), &variables::config::esp::weapon_icon);
                    checkbox(xorstr("paint flags"), &variables::config::esp::flags);
                    checkbox(xorstr("paint distance"), &variables::config::esp::distance);
                    checkbox(xorstr("paint health text"), &variables::config::esp::health);
                    checkbox(xorstr("paint health bar"), &variables::config::esp::health_bar);
                    checkbox(xorstr("paint ammo text"), &variables::config::esp::ammo);
                    checkbox(xorstr("paint ammo bar"), &variables::config::esp::ammo_bar);
                    checkbox(xorstr("paint skeleton"), &variables::config::esp::skeleton);
                    checkbox(xorstr("paint out of fov"), &variables::config::esp::outofview);
                    checkbox(xorstr("paint snapline"), &variables::config::esp::snapline);
                    checkbox(xorstr("paint view angle"), &variables::config::esp::viewangle);
                    checkbox(xorstr("paint thrown grenades"), &variables::config::esp::throwngrenade);
                    checkbox(xorstr("paint thrown grenades icon"), &variables::config::esp::throwngrenade_icon);
                    checkbox(xorstr("paint dropped weapon"), &variables::config::esp::droppedweapon);
                    checkbox(xorstr("paint dropped weapon icon"), &variables::config::esp::droppedweapon_icon);
                    checkbox(xorstr("paint dropped weapon ammo"), &variables::config::esp::droppedweapon_ammo);
                    ImGui::SeparatorText("glow");
                    checkbox(xorstr("draw outline visible"), &variables::config::glow::visible); ImGui::SameLine(); colorpicker(xorstr("visible glow colour"), &variables::config::glow::visible_clr);
                    checkbox(xorstr("draw outline invisible"), &variables::config::glow::occluded); ImGui::SameLine(); colorpicker(xorstr("ocludded glow colour"), &variables::config::glow::occluded_clr);
                    ImGui::SeparatorText("dlight");
                    checkbox(xorstr("draw world model light"), &variables::config::esp::dlight);
                    ImGui::SeparatorText("chams");
                    checkbox(xorstr("draw fill visible model"), &variables::config::chams::visible); ImGui::SameLine(); colorpicker(xorstr("visible chams colour"), &variables::config::chams::visible_clr);
                    checkbox(xorstr("draw fill invisible model"), &variables::config::chams::occluded); ImGui::SameLine(); colorpicker(xorstr("ocludded chams colour"), &variables::config::chams::occluded_clr);
                    checkbox(xorstr("draw fill visible overlay model"), &variables::config::chams::visible_overlay); ImGui::SameLine(); colorpicker(xorstr("visible overlay chams colour"), &variables::config::chams::visible_clr_overlay);
                    checkbox(xorstr("draw fill invisible overlay model"), &variables::config::chams::occluded_overlay); ImGui::SameLine(); colorpicker(xorstr("ocludded overlay chams colour"), &variables::config::chams::occluded_clr_overlay);
                }
                ImGui::PopFont();
            }
            ImGui::EndChild();

            ImGui::SameLine();

            ImGui::BeginChild("settings", third_case_child_group_size, false, ImGuiWindowFlags_None);
            {
                const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::PushFont(textmenufont);
                if (variables::config::esp::fadeinout)
                {
                    sliderfloat(xorstr("fade time"), &variables::config::esp::fadeinout_time, 0.1f, 1.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                if (variables::config::esp::box)
                {
                    if (ImGui::BeginCombo(xorstr("box"), xorstr("style select"), ImGuiComboFlags_NoArrowButton))
                    {
                        ImGui::Selectable(xorstr("rect"), &variables::config::esp::box_rect, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("corner"), &variables::config::esp::box_corner, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("inline"), &variables::config::esp::box_inline, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("outline"), &variables::config::esp::box_outline, ImGuiSelectableFlags_DontClosePopups);

                        ImGui::EndCombo();
                    }
                }
                if (variables::config::esp::flags)
                {
                    if (ImGui::BeginCombo(xorstr("flags"), xorstr("select"), ImGuiComboFlags_NoArrowButton))
                    {
                        ImGui::Selectable(xorstr("armour"), &variables::config::esp::armour, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("balance"), &variables::config::esp::balance, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("flashed"), &variables::config::esp::flashed, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("scoped"), &variables::config::esp::scoped, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("reloading..."), &variables::config::esp::reloading, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("rescuing..."), &variables::config::esp::rescuing, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("defusing..."), &variables::config::esp::defusing, ImGuiSelectableFlags_DontClosePopups);

                        ImGui::EndCombo();
                    }
                }
                if (variables::config::esp::headbox)
                {
                    checkbox(xorstr("head box filled background"), &variables::config::esp::headbox_filled);
                }
                if (variables::config::esp::health)
                {
                    checkbox(xorstr("health text hide suffix"), &variables::config::esp::health_hide_suffix);
                    checkbox(xorstr("health text hide at max"), &variables::config::esp::health_hide_at_max);
                }
                if (variables::config::esp::health_bar)
                {
                    checkbox(xorstr("health bar filled background"), &variables::config::esp::health_bar_background);
                    sliderint(xorstr("health bar size"), &variables::config::esp::health_bar_size, 0, 10, "%d", ImGuiSliderFlags_AlwaysClamp);
                }
                if (variables::config::esp::health || variables::config::esp::health_bar)
                {
                    checkbox(xorstr("color based on health"), &variables::config::esp::health_rgb);
                }
                if (variables::config::esp::ammo_bar)
                {
                    checkbox(xorstr("ammo bar filled background"), &variables::config::esp::ammo_bar_background);
                    sliderint(xorstr("ammo bar size"), &variables::config::esp::ammo_bar_size, 0, 10, "%d", ImGuiSliderFlags_AlwaysClamp);
                }
                if (variables::config::esp::outofview)
                {
                    checkbox(xorstr("out of view visible turn off"), &variables::config::esp::outofview_occluded);
                    sliderfloat(xorstr("out of view size"), &variables::config::esp::outofview_size, 5.00f, 20.00f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    sliderfloat(xorstr("out of view distance"), &variables::config::esp::outofview_distance, 10.00f, 200.00f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                if (variables::config::esp::snapline)
                {
                    if (ImGui::BeginCombo(xorstr("snapline"), xorstr("select position"), ImGuiComboFlags_NoArrowButton))
                    {
                        ImGui::Selectable(xorstr("bottom"), &variables::config::esp::snapline_bottom, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("center"), &variables::config::esp::snapline_center, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("upper"), &variables::config::esp::snapline_upper, ImGuiSelectableFlags_DontClosePopups);

                        ImGui::EndCombo();
                    }
                }
                if (variables::config::esp::skeleton)
                {
                    sliderfloat(xorstr("skeleton thickness"), &variables::config::esp::skeleton_thickness, 0.5f, 2.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                if (variables::config::esp::viewangle)
                {
                    sliderfloat(xorstr("viewangle thickness"), &variables::config::esp::viewangle_thickness, 0.5f, 2.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    sliderfloat(xorstr("viewangle radius"), &variables::config::esp::viewangle_distance, 20.0f, 250.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                if (variables::config::esp::snapline)
                {
                    sliderfloat(xorstr("snapline thickness"), &variables::config::esp::snapline_thickness, 0.5f, 2.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                if (variables::config::glow::visible)
                {
                    ImGui::Combo(xorstr("style glow"), &variables::config::glow::visible_style, xorstr("basic\0pulsing\0outline\0outline pulsing\0"));
                }
                if (variables::config::esp::dlight)
                {
                    sliderfloat(xorstr("dlight radius"), &variables::config::esp::dlight_radius, 50.0f, 200.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                if (variables::config::chams::visible)
                {
                    ImGui::Combo(xorstr("visible style chams"), &variables::config::chams::visible_style, xorstr("regular\0flat\0metalic\0plastic\0elixir\0glow\0wireframe\0crystal\0space\0glass\0"));
                }
                if (variables::config::chams::occluded)
                {
                    ImGui::Combo(xorstr("occluded style chams"), &variables::config::chams::occluded_style, xorstr("regular\0flat\0metalic\0plastic\0elixir\0glow\0wireframe\0crystal\0space\0glass\0"));
                }
                if (variables::config::chams::visible_overlay)
                {
                    ImGui::Combo(xorstr("overlay visible style model"), &variables::config::chams::visible_style_overlay, xorstr("regular\0flat\0metalic\0plastic\0elixir\0glow\0wireframe\0crystal\0space\0glass\0"));
                    checkbox(xorstr("overlay visible wireframe"), &variables::config::chams::visible_wireframe_overlay);
                }
                if (variables::config::chams::occluded_overlay)
                {
                    ImGui::Combo(xorstr("overlay occluded style model"), &variables::config::chams::occluded_style_overlay, xorstr("regular\0flat\0metalic\0plastic\0elixir\0glow\0wireframe\0crystal\0space\0glass\0"));
                    checkbox(xorstr("overlay occluded wireframe"), &variables::config::chams::occluded_wireframe_overlay);
                }
                ImGui::PopFont();
            }
            ImGui::EndChild();
            break;
       case 3:
            ImGui::SetCursorPos(base_first_child_position);
            ImGui::BeginChild("child 1", second_case_child_group_size, false, ImGuiWindowFlags_None);
            {
                const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::PushFont(textmenufont);

                ImGui::PopFont();
            }
            ImGui::EndChild();

            ImGui::SameLine();
            ImGui::BeginChild("child 2", second_case_child_group_size, false, ImGuiWindowFlags_None);
            {
                const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::PushFont(textmenufont);

                ImGui::PopFont();
            }
            ImGui::EndChild();

            ImGui::Spacing();
            ImGui::SetCursorPosX(5);
            ImGui::BeginChild("child 3", second_case_child_group_size, false, ImGuiWindowFlags_None);
            {
                const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::PushFont(textmenufont);

                ImGui::PopFont();
            }
            ImGui::EndChild();

            ImGui::SameLine();
            ImGui::BeginChild("child 4", second_case_child_group_size, false, ImGuiWindowFlags_None);
            {
                const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::PushFont(textmenufont);

                ImGui::PopFont();
            }
            ImGui::EndChild();
            break;
        case 4: 
            ImGui::SetCursorPos(base_first_child_position);
            ImGui::BeginChild("screen", second_case_child_group_size, false, ImGuiWindowFlags_None);
            {
                const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::PushFont(textmenufont);
                checkbox(xorstr("watermark"), &variables::config::misc::watermark);
                checkbox(xorstr("music display"), &variables::config::misc::spotify);
                checkbox(xorstr("spectator list"), &variables::config::misc::spectatorlist);
                if (variables::config::misc::spectatorlist)
                {
                    checkbox(xorstr("mode"), &variables::config::misc::spectatorlist_mode);
                }
                checkbox(xorstr("sniper crosshair"), &variables::config::misc::snipercrosshair);
                ImGui::PopFont();
            }
            ImGui::EndChild();

            ImGui::SameLine();
            ImGui::BeginChild("convars", second_case_child_group_size, false, ImGuiWindowFlags_None);
            {
                const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::PushFont(textmenufont);
                checkbox(xorstr("force crosshair"), &variables::config::misc::forcecrosshair);
                checkbox(xorstr("recoil crosshair"), &variables::config::misc::recoilcrosshair);
                checkbox(xorstr("change viewmodel offsets"), &variables::config::misc::changeviewmodeloffsets);
                if (variables::config::misc::changeviewmodeloffsets)
                {
                    sliderfloat(xorstr("offset x"), &variables::config::misc::viewmodeloffset_x, -25.0f, 25.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    sliderfloat(xorstr("offset y"), &variables::config::misc::viewmodeloffset_y, -25.0f, 25.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    sliderfloat(xorstr("offset z"), &variables::config::misc::viewmodeloffset_z, -25.0f, 25.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                checkbox(xorstr("change fov offset"), &variables::config::misc::changeviewmodelfov);
                if (variables::config::misc::changeviewmodelfov)
                {
                    sliderfloat(xorstr("viewmodel fov"), &variables::config::misc::viewmodelfov, 54.0f, 125.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                checkbox(xorstr("change viewsway offset"), &variables::config::misc::changeweaponswayscale);
                if (variables::config::misc::changeweaponswayscale)
                {
                    sliderfloat(xorstr("weapon sway scale"), &variables::config::misc::weaponswayscale, 0.0f, 100.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                if (ImGui::BeginCombo(xorstr("removes"), xorstr("select remove"), ImGuiComboFlags_NoArrowButton))
                {
                    ImGui::Selectable(xorstr("wireframe smoke"), &variables::config::misc::removewireframesmoke, ImGuiSelectableFlags_DontClosePopups);
                    ImGui::Selectable(xorstr("wireframe fire"), &variables::config::misc::removewireframefire, ImGuiSelectableFlags_DontClosePopups);
                    ImGui::Selectable(xorstr("full smoke"), &variables::config::misc::removefullsmoke, ImGuiSelectableFlags_DontClosePopups);
                    ImGui::Selectable(xorstr("full fire"), &variables::config::misc::removefullfire, ImGuiSelectableFlags_DontClosePopups);
                    ImGui::Selectable(xorstr("flash"), &variables::config::misc::removeflash, ImGuiSelectableFlags_DontClosePopups);
              
                    ImGui::EndCombo();
                }
                if (variables::config::misc::removeflash)
                {
                    sliderint(xorstr("remove flash reduce"), &variables::config::misc::removeflash_time, 0, 100, "%d", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::PopFont();
            }
            ImGui::EndChild();

            ImGui::Spacing();
            ImGui::SetCursorPosX(5);
            ImGui::BeginChild("general", second_case_child_group_size, false, ImGuiWindowFlags_None);
            {
                const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::PushFont(textmenufont);
                checkbox(xorstr("auto accept"), &variables::config::misc::autoaccept);
                checkbox(xorstr("rank reveal"), &variables::config::misc::rankreveal);
                checkbox(xorstr("use key spammer"), &variables::config::misc::usekeyspam); 
                ImGui::PopFont();
            }
            ImGui::EndChild();

            ImGui::SameLine();
            ImGui::BeginChild("extra", second_case_child_group_size, false, ImGuiWindowFlags_None);
            {
                const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::PushFont(textmenufont);
                checkbox(xorstr("unlock inventory"), &variables::config::misc::unlockinventory);
                checkbox(xorstr("region changer"), &variables::config::misc::regionchanger);
                if (variables::config::misc::regionchanger)
                {
                    ImGui::Combo(xorstr("region type"), &variables::config::misc::regionchanger_type, xorstr("Australia\0Austria\0Brazil\0Chile\0Dubai\0France\0Germany\0Hong Kong\0India (Chennai)\0India (Mumbai)\0Japan\0Luxembourg\0Netherlands\0Peru\0Philipines\0Poland\0Singapore\0South Africa\0Spain\0Sweden\0UK\0USA (Atlanta)\0USA (Seattle)\0USA (Chicago)\0USA (Los Angeles)\0USA (Moses Lake)\0USA (Oklahoma)\0USA (Seattle)\0USA (Washington DC)\0"));
                }
                ImGui::PopFont();
            }
            ImGui::EndChild();
            break;
        case 5:   
            ImGui::SetCursorPos(base_first_child_position);
            ImGui::BeginChild("move", third_case_child_group_size, false, ImGuiWindowFlags_None);
            {
                const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::PushFont(textmenufont);
                checkbox(xorstr("bhop"), &variables::config::movement::bunnyhop);
                checkbox(xorstr("edge jump"), &variables::config::movement::edgejump); ImGui::SameLine(); keybind(xorstr("edge jump key"), &variables::config::movement::edgejump_key, &variables::config::movement::edgejump_key_type);
                if (variables::config::movement::edgejump)
                {
                    checkbox(xorstr("edge jump block buttons"), &variables::config::movement::edgejump_blockbuttons);
                }
                checkbox(xorstr("mini jump"), &variables::config::movement::minijump); ImGui::SameLine(); keybind(xorstr("mini jump key"), &variables::config::movement::minijump_key, &variables::config::movement::minijump_key_type);
                if (variables::config::movement::minijump)
                {
                    checkbox(xorstr("mini jump force edgejump"), &variables::config::movement::minijump_forceedgejump);
                    checkbox(xorstr("mini jump block buttons"), &variables::config::movement::minijump_blockbuttons);
                }
                checkbox(xorstr("long jump"), &variables::config::movement::longjump); ImGui::SameLine(); keybind(xorstr("long jump key"), &variables::config::movement::longjump_key, &variables::config::movement::minijump_key_type);
                if (variables::config::movement::longjump)
                {
                   checkbox(xorstr("long jump force edgejump"), &variables::config::movement::longjump_forceedgejump);
                   checkbox(xorstr("long jump block buttons"), &variables::config::movement::longjump_blockbuttons);
                }
                checkbox(xorstr("ladder edge jump"), &variables::config::movement::ladderedgejump); ImGui::SameLine(); keybind(xorstr("ladder edge jump key"), &variables::config::movement::ladderedgejump_key, &variables::config::movement::ladderedgejump_key_type);
                if (variables::config::movement::ladderedgejump)
                {
                    checkbox(xorstr("ladder edge jump block buttons"), &variables::config::movement::ladderedgejump_blockbuttons);
                }
                checkbox(xorstr("jump bug"), &variables::config::movement::jumpbug); ImGui::SameLine(); keybind(xorstr("jump bug key"), &variables::config::movement::jumpbug_key, &variables::config::movement::jumpbug_key_type);
                checkbox(xorstr("auto duck"), &variables::config::movement::autoduck); ImGui::SameLine(); keybind(xorstr("auto duck key"), &variables::config::movement::autoduck_key, &variables::config::movement::autoduck_key_type);
                if (variables::config::movement::autoduck)
                {
                    sliderfloat(xorstr("auto duck time"), &variables::config::movement::autoduck_time, 0.00f, 1.00f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                checkbox(xorstr("edge bug"), &variables::config::movement::edgebug); ImGui::SameLine(); keybind(xorstr("edge bug key"), &variables::config::movement::edgebug_key, &variables::config::movement::edgebug_key_type);
                if (variables::config::movement::edgebug)
                {
                    checkbox(xorstr("edge bug block buttons"), &variables::config::movement::edgebug_blockbuttons);
                    checkbox(xorstr("edge bug asist to edge/advanced detection"), &variables::config::movement::edgebug_strafetoedge);
                    sliderint(xorstr("edge bug ticks"), &variables::config::movement::edgebug_ticks, 0, 128, "%d", ImGuiSliderFlags_AlwaysClamp);
                    sliderfloat(xorstr("edge bug strength lock"), &variables::config::movement::edgebug_lock, 1.0f, 100.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                checkbox(xorstr("auto align"), &variables::config::movement::autoalign); ImGui::SameLine(); keybind(xorstr("auto align key"), &variables::config::movement::autoalign_key, &variables::config::movement::autoalign_key_type);
                checkbox(xorstr("auto pixel surf"), &variables::config::movement::pixelsurf); ImGui::SameLine(); keybind(xorstr("auto pixel surf key"), &variables::config::movement::pixelsurf_key, &variables::config::movement::pixelsurf_key_type);
                checkbox(xorstr("mouse speed limit"), &variables::config::movement::msl); ImGui::SameLine(); keybind(xorstr("mouse speed limiter key"), &variables::config::movement::msl_key, &variables::config::movement::msl_key_type);
                if (variables::config::movement::msl)
                {
                    sliderfloat(xorstr("msl strength x"), &variables::config::movement::msl_strength_x, 0.0f, 100.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    sliderfloat(xorstr("msl strength y"), &variables::config::movement::msl_strength_y, 0.0f, 100.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                checkbox(xorstr("stamina hop"), &variables::config::movement::staminahop); ImGui::SameLine(); keybind(xorstr("stamina hop key"), &variables::config::movement::staminahop_key, &variables::config::movement::staminahop_key_type);
                if (variables::config::movement::staminahop)
                {
                    sliderint(xorstr("stamina hop ticks"), &variables::config::movement::staminahop_ticks, 0, 12, "%d", ImGuiSliderFlags_AlwaysClamp);
                }
                checkbox(xorstr("infinity duck"), &variables::config::movement::infinityduck);
                if (ImGui::BeginCombo(xorstr("block buttons"), xorstr("select"), ImGuiComboFlags_NoArrowButton))
                {
                    ImGui::Selectable(xorstr("forward"), &variables::config::movement::blockbutton_forward, ImGuiSelectableFlags_DontClosePopups);
                    ImGui::Selectable(xorstr("back"), &variables::config::movement::blockbutton_back, ImGuiSelectableFlags_DontClosePopups);
                    ImGui::Selectable(xorstr("left"), &variables::config::movement::blockbutton_left, ImGuiSelectableFlags_DontClosePopups);
                    ImGui::Selectable(xorstr("right"), &variables::config::movement::blockbutton_right, ImGuiSelectableFlags_DontClosePopups);

                    ImGui::EndCombo();
                }
                checkbox(xorstr("block bot"), &variables::config::movement::blockbot); ImGui::SameLine(); keybind(xorstr("block bot key"), &variables::config::movement::blockbot_key, &variables::config::movement::blockbot_key_type);
                checkbox(xorstr("jump stats"), &variables::config::movement::jumpstats);
                ImGui::PopFont();
            }
            ImGui::EndChild();

            ImGui::SameLine();

            ImGui::BeginChild("indicators", third_case_child_group_size, false, ImGuiWindowFlags_None);
            {
                const float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::PushFont(textmenufont);
                checkbox(xorstr("velocity"), &variables::config::indicators::velocity);
                if (variables::config::indicators::velocity)
                {
                    ImGui::Combo(xorstr("velocity style"), &variables::config::indicators::velocity_style, xorstr("classic\0rainbow\0fade\0"));
                    checkbox(xorstr("velocity takeoff on ground"), &variables::config::indicators::velocity_takeoff_on_ground);
                    sliderfloat(xorstr("velocity fade strength"), &variables::config::indicators::velocity_fade_strength, 255.0f, 360.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    sliderfloat(xorstr("velocity rainbow hue"), &variables::config::indicators::velocity_rainbow_hue, 320.0f, 1436.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    sliderfloat(xorstr("velocity rainbow saturation"), &variables::config::indicators::velocity_rainbow_saturation, 0.0f, 1.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                checkbox(xorstr("stamina"), &variables::config::indicators::stamina);
                if (variables::config::indicators::stamina)
                {
                    ImGui::Combo(xorstr("stamina style"), &variables::config::indicators::stamina_style, xorstr("classic\0rainbow\0fade\0"));
                    checkbox(xorstr("stamina takeoff on ground"), &variables::config::indicators::stamina_takeoff_on_ground);
                    sliderfloat(xorstr("stamina fade strength"), &variables::config::indicators::stamina_fade_strength, 35.0f, 50.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    sliderfloat(xorstr("stamina rainbow hue"), &variables::config::indicators::stamina_rainbow_hue, 32.0f, 60.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    sliderfloat(xorstr("stamina rainbow saturation"), &variables::config::indicators::stamina_rainbow_saturation, 0.0f, 1.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                checkbox(xorstr("velocity graph"), &variables::config::indicators::velocitygraph);
                checkbox(xorstr("stamina graph"), &variables::config::indicators::staminagraph);
                if (variables::config::indicators::velocitygraph || variables::config::indicators::staminagraph)
                {
                    sliderfloat(xorstr("graph scale"), &variables::config::indicators::graph_scale, 0.40f, 2.70f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                checkbox(xorstr("bind indicators"), &variables::config::indicators::indicators);
                if (variables::config::indicators::indicators)
                {
                    if (ImGui::BeginCombo(xorstr("indicators"), xorstr("select"), ImGuiComboFlags_NoArrowButton))
                    {
                        ImGui::Selectable(xorstr("jumpbug"), &variables::config::indicators::jumpbug, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("edgebug"), &variables::config::indicators::edgebug, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("edgejump"), &variables::config::indicators::edgejump, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("longjump"), &variables::config::indicators::longjump, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("minijump"), &variables::config::indicators::minijump, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("autoduck"), &variables::config::indicators::autoduck, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("pixelsurf"), &variables::config::indicators::pixelsurf, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("autoalign"), &variables::config::indicators::autoalign, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("staminahop"), &variables::config::indicators::staminahop, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("msl"), &variables::config::indicators::msl, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::EndCombo();
                    }
                    sliderfloat(xorstr("indicators speed"), &variables::config::indicators::speed, 1.25f, 25.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    sliderfloat(xorstr("indicators sameline"), &variables::config::indicators::sameline, 0.0f, 10.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                sliderint(xorstr("indicators position"), &variables::config::indicators::indicator_position, 0, 540, "%d", ImGuiSliderFlags_AlwaysClamp);
                ImGui::PopFont();
            }
            ImGui::EndChild(); 
            break;
        case 6: break;
        case 7: break; 
        }
    }
    ImGui::End();
    ImGui::PopFont();
    ImGui::PopStyleVar(4);
    ImGui::PopStyleColor(36);
/*
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(127 / 255.f, 149 / 255.f, 209 / 255.f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(127 / 255.f, 149 / 255.f, 209 / 255.f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(97 / 255.f, 119 / 255.f, 179 / 255.f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(32 / 255.f, 32 / 255.f, 32 / 255.f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(23 / 255.f, 23 / 255.f, 23 / 255.f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(23 / 255.f, 23 / 255.f, 23 / 255.f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(23 / 255.f, 23 / 255.f, 23 / 255.f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(16 / 255.f, 16 / 255.f, 16 / 255.f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.06f, 0.06f, 0.06f, 1.0f));
    ImGui::SetWindowSize(ImVec2(510, 535));
    ImGui::SetNextWindowSizeConstraints(ImVec2(510, 535), ImVec2(650, 730));
    ImGui::Begin(xorstr("weiamware-imgui-menu"), NULL, ImGuiWindowFlags_NoDecoration);
    {
        ImVec2 posmenu = ImGui::GetWindowPos();
        float posmenuwidth = ImGui::GetWindowWidth();
        float posmenuheight = ImGui::GetWindowHeight();

        ImGui::GetWindowDrawList()->AddText(menutextfont, 12.0f, ImVec2(posmenu.x + 11, posmenu.y + 11), ImColor(0.0f, 0.0f, 0.0f, 1.0f), xorstr("weiamware"));
        ImGui::GetWindowDrawList()->AddText(menutextfont, 12.0f, ImVec2(posmenu.x + 10, posmenu.y + 10), ImColor(1.0f, 1.0f, 1.0f, 1.0f), xorstr("weiamware"));
        ImGui::GetWindowDrawList()->AddRect(ImVec2(posmenu.x + 10, posmenu.y + 30), ImVec2(posmenu.x + posmenuwidth - 10, posmenu.y + posmenuheight - 10), ImColor(0.2f, 0.2f, 0.2f, 1.0f), 0.0f, 0, 1.0f);

        ImGui::SetCursorPos({ posmenuwidth - 275, 6.3 });
        if (ImGui::Tab(xorstr("rage"), tabs == 0))
        {
           tabs = 0;
        }

        ImGui::SameLine();
        if (ImGui::Tab(xorstr("legit"), tabs == 1))
        {
            tabs = 1;
        }

        ImGui::SameLine();
        if (ImGui::Tab(xorstr("visuals"), tabs == 2))
        {
            tabs = 2;
        }

        ImGui::SameLine();
        if (ImGui::Tab(xorstr("misc"), tabs == 3))
        {
            tabs = 3;
        }
        ImGui::Checkbox;
        ImGui::SameLine();
        if (ImGui::Tab(xorstr("skins"), tabs == 4))
        {
            tabs = 4;
        }

        ImGui::SameLine();
        if (ImGui::Tab(xorstr("fonts"), tabs == 5))
        {
            tabs = 5;
        }

        ImGui::SameLine();
        if (ImGui::Tab(xorstr("lua"), tabs == 6))
        {
            tabs = 6;
        }

        ImGui::SameLine();
        if (ImGui::Tab(xorstr("mr"), tabs == 7))
        {
            tabs = 7;
        }


        auto rage_group_size = ImVec2(posmenuwidth / 2 - 25, posmenuheight / 2 - 35);

        auto legit_group_size = ImVec2(posmenuwidth / 2 - 25, posmenuheight / 2 - 35);

        auto visuals_group_size = ImVec2(posmenuwidth / 2 - 25, posmenuheight / 2 - 35);

        auto misc_group_size = ImVec2(posmenuwidth / 2 - 25, posmenuheight / 2 - 35);

        auto skins_group_size = ImVec2(posmenuwidth / 2 - 25, posmenuheight / 2 - 35);

        auto fonts_group_size = ImVec2(posmenuwidth / 2 - 25, posmenuheight / 2 - 35);

        auto lua_group_size = ImVec2(posmenuwidth / 2 - 25, posmenuheight / 2 - 35);

        auto mr_group_size = ImVec2(posmenuwidth / 2 - 25, posmenuheight / 2 - 35);

        switch (tabs)
        {
        case 0:
            ImGui::SetCursorPos(ImVec2(20, 40));
            ImGui::BeginChild(xorstr("general"), rage_group_size, true);
            {
                float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::Text(xorstr("hello world!"));
                
                //ImGui::Combo("test 5", &combo, "1");
                //ImGui::InputText("test 6", &text, 32, ImGuiInputTextFlags_EnterReturnsTrue);
            }
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::BeginChild(xorstr("settings"), rage_group_size, true);
            {

            }
            ImGui::EndChild();
            ImGui::Spacing();
            ImGui::SetCursorPosX(20);
            ImGui::BeginChild(xorstr("backtrack"), rage_group_size, true);
            {

            }
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::BeginChild(xorstr("triggerbot"), rage_group_size, true);
            {

            }
            ImGui::EndChild();
            break;
        case 1:
            if (subtab == 0)
            {
                aimbot_page(rage_group_size, variables::config::aimbot::general);
            }

            if (subtab == 1)
            {
                aimbot_page(rage_group_size, variables::config::aimbot::pistols, true);
            }

            if (subtab == 2)
            {
                aimbot_page(rage_group_size, variables::config::aimbot::heavy_pistols, true);
            }

            if (subtab == 3)
            {
                aimbot_page(rage_group_size, variables::config::aimbot::smg, true);
            }

            if (subtab == 4)
            {
                aimbot_page(rage_group_size, variables::config::aimbot::shotguns, true);
            }

            if (subtab == 5)
            {
                aimbot_page(rage_group_size, variables::config::aimbot::rifles, true);
            }

            if (subtab == 6)
            {
                aimbot_page(rage_group_size, variables::config::aimbot::snipers, true);
            }
            break;
        case 2:
            ImGui::SetCursorPos(ImVec2(20, 40));
            ImGui::BeginChild(xorstr("esp"), rage_group_size, true);
            {
                float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::Checkbox(xorstr("enable esp"), &variables::config::esp::enable); ImGui::SameLine(); colorpicker(xorstr("visible esp colour"), &variables::config::esp::visible_clr); ImGui::SameLine(); colorpicker(xorstr("ocludded esp colour"), &variables::config::esp::occluded_clr); ImGui::SameLine(); ImGui::KeyBind(xorstr("draw key"), &variables::config::esp::key, &variables::config::esp::key_type);
                if (variables::config::esp::enable)
                {
                    ImGui::Checkbox(xorstr("engine radar"), &variables::config::esp::engine_radar);
                    ImGui::Checkbox(xorstr("paint on teammates"), &variables::config::esp::teammates);
                    ImGui::Checkbox(xorstr("paint fade in/out"), &variables::config::esp::fadeinout);
                    ImGui::Checkbox(xorstr("paint box"), &variables::config::esp::box);
                    ImGui::Checkbox(xorstr("paint name"), &variables::config::esp::name);
                    ImGui::Checkbox(xorstr("paint weapon"), &variables::config::esp::weapon);
                    ImGui::Checkbox(xorstr("paint weapon icon"), &variables::config::esp::weapon_icon);
                    ImGui::Checkbox(xorstr("paint flags"), &variables::config::esp::flags);
                    ImGui::Checkbox(xorstr("paint health text"), &variables::config::esp::health);
                    ImGui::Checkbox(xorstr("paint health bar"), &variables::config::esp::health_bar);
                    ImGui::Checkbox(xorstr("paint ammo bar"), &variables::config::esp::ammo_bar);
                    ImGui::Checkbox(xorstr("paint skeleton"), &variables::config::esp::skeleton);
                    ImGui::Checkbox(xorstr("paint out of fov"), &variables::config::esp::outofview);
                    ImGui::Checkbox(xorstr("paint snapline"), &variables::config::esp::snapline);
                }
            }
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::BeginChild(xorstr("settings"), rage_group_size, true);
            {
                if (variables::config::esp::fadeinout)
                {
                    ImGui::SliderFloat(xorstr("fade time"), &variables::config::esp::fadeinout_time, 0.1f, 1.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                if (variables::config::esp::box)
                {
                    if (ImGui::BeginCombo(xorstr("box"), xorstr("style select"), ImGuiComboFlags_NoArrowButton))
                    {
                        ImGui::Selectable(xorstr("rect"), &variables::config::esp::box_rect, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("corner"), &variables::config::esp::box_corner, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("inline"), &variables::config::esp::box_inline, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("outline"), &variables::config::esp::box_outline, ImGuiSelectableFlags_DontClosePopups);

                        ImGui::EndCombo();
                    }
                }
                if (variables::config::esp::flags)
                {
                    if (ImGui::BeginCombo(xorstr("flags"), xorstr("select"), ImGuiComboFlags_NoArrowButton))
                    {
                        ImGui::Selectable(xorstr("armour"), &variables::config::esp::armour, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("balance"), &variables::config::esp::balance, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("flashed"), &variables::config::esp::flashed, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("scoped"), &variables::config::esp::scoped, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("reloading..."), &variables::config::esp::reloading, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("rescuing..."), &variables::config::esp::rescuing, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("defusing..."), &variables::config::esp::defusing, ImGuiSelectableFlags_DontClosePopups);

                        ImGui::EndCombo();
                    }
                }
                if (variables::config::esp::health)
                {
                    ImGui::Checkbox(xorstr("health text hide suffix"), &variables::config::esp::health_hide_suffix);
                    ImGui::Checkbox(xorstr("health text hide at max"), &variables::config::esp::health_hide_at_max);
                    ImGui::Checkbox(xorstr("health text gradient"), &variables::config::esp::health_rgb);
                }
                if (variables::config::esp::health_bar)
                {
                    ImGui::Checkbox(xorstr("health bar filled background"), &variables::config::esp::health_bar_background);
                    ImGui::SliderInt(xorstr("health bar size"), &variables::config::esp::health_bar_size, 0, 10, "%d", ImGuiSliderFlags_AlwaysClamp);
                }
                if (variables::config::esp::ammo_bar)
                {
                    ImGui::Checkbox(xorstr("ammo bar filled background"), &variables::config::esp::ammo_bar_background);
                    ImGui::SliderInt(xorstr("ammo bar size"), &variables::config::esp::ammo_bar_size, 0, 10, "%d", ImGuiSliderFlags_AlwaysClamp);
                }
                if (variables::config::esp::outofview)
                {
                    ImGui::SliderFloat(xorstr("out of view size"), &variables::config::esp::outofview_size, 5.00f, 20.00f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat(xorstr("out of view distance"), &variables::config::esp::outofview_distance, 10.00f, 200.00f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                if (variables::config::esp::snapline)
                {
                    if (ImGui::BeginCombo(xorstr("snapline"), xorstr("select position"), ImGuiComboFlags_NoArrowButton))
                    {
                        ImGui::Selectable(xorstr("bottom"), &variables::config::esp::snapline_bottom, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("center"), &variables::config::esp::snapline_center, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("upper"), &variables::config::esp::snapline_upper, ImGuiSelectableFlags_DontClosePopups);

                        ImGui::EndCombo();
                    }
                }
                if (variables::config::glow::visible)
                {
                    ImGui::Combo(xorstr("style glow"), &variables::config::glow::visible_style, xorstr("basic\0pulsing\0outline\0outline pulsing\0"));
                }
                if (variables::config::chams::visible)
                {
                    ImGui::Combo(xorstr("visible style chams"), &variables::config::chams::visible_style, xorstr("regular\0flat\0metalic\0plastic\0elixir\0glow\0wireframe\0crystal\0space\0glass\0"));
                }
                if (variables::config::chams::occluded)
                {
                    ImGui::Combo(xorstr("occluded style chams"), &variables::config::chams::occluded_style, xorstr("regular\0flat\0metalic\0plastic\0elixir\0glow\0wireframe\0crystal\0space\0glass\0"));
                }
                if (variables::config::esp::dlight)
                {
                    ImGui::SliderFloat(xorstr("dlight radius"), &variables::config::esp::dlight_radius, 50.0f, 200.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
            }
            ImGui::EndChild();
            ImGui::Spacing();
            ImGui::SetCursorPosX(20);
            ImGui::BeginChild(xorstr("glow"), rage_group_size, true);
            {
                if (variables::config::esp::enable)
                {
                    ImGui::Checkbox(xorstr("visible glow"), &variables::config::glow::visible); ImGui::SameLine(); colorpicker(xorstr("visible glow colour"), &variables::config::glow::visible_clr);
                    ImGui::Checkbox(xorstr("invisible glow"), &variables::config::glow::occluded); ImGui::SameLine(); colorpicker(xorstr("ocludded glow colour"), &variables::config::glow::occluded_clr); 
                    ImGui::Checkbox(xorstr("world glow (dlights)"), &variables::config::esp::dlight);
                }
            }
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::BeginChild(xorstr("chams"), rage_group_size, true);
            {
                if (variables::config::esp::enable)
                {
                    ImGui::Checkbox(xorstr("visible chams"), &variables::config::chams::visible); ImGui::SameLine(); colorpicker(xorstr("visible chams colour"), &variables::config::chams::visible_clr);
                    ImGui::Checkbox(xorstr("invisible chams"), &variables::config::chams::occluded); ImGui::SameLine(); colorpicker(xorstr("ocludded chams colour"), &variables::config::chams::occluded_clr);
                }
            }
            ImGui::EndChild();
            break;
        case 3:
            ImGui::SetCursorPos(ImVec2(20, 40));
            ImGui::BeginChild(xorstr("main"), misc_group_size, true);
            {
                float group_w = ImGui::GetCurrentWindow()->Size.x - ImGui::GetStyle().FramePadding.x * 2;

                ImGui::Text(xorstr("menu key")); ImGui::SameLine(); ImGui::KeyBind(xorstr("menu key"), &variables::config::misc::menukeybind);
                ImGui::Checkbox(xorstr("auto accept"), &variables::config::misc::autoaccept);
                ImGui::Checkbox(xorstr("watermark"), &variables::config::misc::watermark);
                ImGui::Checkbox(xorstr("music display"), &variables::config::misc::spotify);
                ImGui::Checkbox(xorstr("spectator list"), &variables::config::misc::spectatorlist);
                if (variables::config::misc::spectatorlist)
                {
                    ImGui::Checkbox(xorstr("mode"), &variables::config::misc::spectatorlist_mode);
                }
                ImGui::Checkbox(xorstr("rank reveal"), &variables::config::misc::rankreveal);
                ImGui::Checkbox(xorstr("unlock inventory"), &variables::config::misc::unlockinventory);
                ImGui::Checkbox(xorstr("region changer"), &variables::config::misc::regionchanger);
                if (variables::config::misc::regionchanger)
                {
                    ImGui::Combo(xorstr("region type"), &variables::config::misc::regionchanger_type, xorstr("Australia\0Austria\0Brazil\0Chile\0Dubai\0France\0Germany\0Hong Kong\0India (Chennai)\0India (Mumbai)\0Japan\0Luxembourg\0Netherlands\0Peru\0Philipines\0Poland\0Singapore\0South Africa\0Spain\0Sweden\0UK\0USA (Atlanta)\0USA (Seattle)\0USA (Chicago)\0USA (Los Angeles)\0USA (Moses Lake)\0USA (Oklahoma)\0USA (Seattle)\0USA (Washington DC)\0"));
                }
                ImGui::Checkbox(xorstr("door spammer"), &variables::config::misc::doorspam); ImGui::SameLine(); ImGui::KeyBind(xorstr("door spammer key"), &variables::config::misc::doorspam_key, &variables::config::misc::doorspam_key_type);
                ImGui::Checkbox(xorstr("sniper crosshair"), &variables::config::misc::snipercrosshair);
                ImGui::Checkbox(xorstr("force crosshair"), &variables::config::misc::forcecrosshair);
                ImGui::Checkbox(xorstr("recoil crosshair"), &variables::config::misc::recoilcrosshair);
                ImGui::Checkbox(xorstr("change viewmodel offsets"), &variables::config::misc::changeviewmodeloffsets);
                if (variables::config::misc::changeviewmodeloffsets)
                {
                    ImGui::SliderFloat(xorstr("offset x"), &variables::config::misc::viewmodeloffset_x, -25.0f, 25.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat(xorstr("offset y"), &variables::config::misc::viewmodeloffset_y, -25.0f, 25.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat(xorstr("offset z"), &variables::config::misc::viewmodeloffset_z, -25.0f, 25.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::Checkbox(xorstr("change fov offset"), &variables::config::misc::changeviewmodelfov);
                if (variables::config::misc::changeviewmodelfov)
                {
                    ImGui::SliderFloat(xorstr("viewmodel fov"), &variables::config::misc::viewmodelfov, 54.0f, 125.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::Checkbox(xorstr("change viewsway offset"), &variables::config::misc::changeweaponswayscale);
                if (variables::config::misc::changeweaponswayscale)
                {
                    ImGui::SliderFloat(xorstr("weapon sway scale"), &variables::config::misc::weaponswayscale, 0.0f, 100.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
            }
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::BeginChild(xorstr("indicators"), misc_group_size, true);
            {
                ImGui::Checkbox(xorstr("velocity"), &variables::config::indicators::velocity);
                if (variables::config::indicators::velocity)
                {
                    ImGui::Combo(xorstr("velocity style"), &variables::config::indicators::velocity_style, "classic\0rainbow\0fade\0");
                    ImGui::Checkbox(xorstr("velocity takeoff on ground"), &variables::config::indicators::velocity_takeoff_on_ground);
                    ImGui::SliderFloat(xorstr("velocity fade strength"), &variables::config::indicators::velocity_fade_strength, 255.0f, 360.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat(xorstr("velocity rainbow hue"), &variables::config::indicators::velocity_rainbow_hue, 320.0f, 1436.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat(xorstr("velocity rainbow saturation"), &variables::config::indicators::velocity_rainbow_saturation, 0.0f, 1.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::Checkbox(xorstr("stamina"), &variables::config::indicators::stamina);
                if (variables::config::indicators::stamina)
                {
                    ImGui::Combo(xorstr("stamina style"), &variables::config::indicators::stamina_style, "classic\0rainbow\0fade\0");
                    ImGui::Checkbox(xorstr("stamina takeoff on ground"), &variables::config::indicators::stamina_takeoff_on_ground);
                    ImGui::SliderFloat(xorstr("stamina fade strength"), &variables::config::indicators::stamina_fade_strength, 35.0f, 50.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat(xorstr("stamina rainbow hue"), &variables::config::indicators::stamina_rainbow_hue, 32.0f, 60.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat(xorstr("stamina rainbow saturation"), &variables::config::indicators::stamina_rainbow_saturation, 0.0f, 1.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::Checkbox(xorstr("velocity graph"), &variables::config::indicators::velocitygraph);
                ImGui::Checkbox(xorstr("stamina graph"), &variables::config::indicators::staminagraph);
                if (variables::config::indicators::velocitygraph || variables::config::indicators::staminagraph)
                {
                    ImGui::SliderFloat(xorstr("graph scale"), &variables::config::indicators::graph_scale, 0.40f, 2.70f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::Checkbox(xorstr("bind indicators"), &variables::config::indicators::indicators);
                if (variables::config::indicators::indicators)
                {
                    if (ImGui::BeginCombo(xorstr("indicators"), xorstr("select"), ImGuiComboFlags_NoArrowButton))
                    {
                        ImGui::Selectable(xorstr("jumpbug"), &variables::config::indicators::jumpbug, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("edgebug"), &variables::config::indicators::edgebug, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("edgejump"), &variables::config::indicators::edgejump, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("longjump"), &variables::config::indicators::longjump, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("minijump"), &variables::config::indicators::minijump, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("autoduck"), &variables::config::indicators::autoduck, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("pixelsurf"), &variables::config::indicators::pixelsurf, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("autoalign"), &variables::config::indicators::autoalign, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("staminahop"), &variables::config::indicators::staminahop, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::Selectable(xorstr("msl"), &variables::config::indicators::msl, ImGuiSelectableFlags_DontClosePopups);
                        ImGui::EndCombo();
                    }
                    ImGui::SliderFloat(xorstr("indicators speed"), &variables::config::indicators::speed, 1.25f, 25.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat(xorstr("indicators sameline"), &variables::config::indicators::sameline, 0.0f, 10.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::SliderInt(xorstr("indicators position"), &variables::config::indicators::indicator_position, 0, 540, "%d", ImGuiSliderFlags_AlwaysClamp);
            }
            ImGui::EndChild();
            ImGui::Spacing();
            ImGui::SetCursorPosX(20);
            ImGui::BeginChild(xorstr("movement"), misc_group_size, true);
            {
                ImGui::Checkbox(xorstr("bhop"), &variables::config::movement::bunnyhop);
                ImGui::Checkbox(xorstr("edge jump"), &variables::config::movement::edgejump); ImGui::SameLine(); ImGui::KeyBind(xorstr("edge jump key"), &variables::config::movement::edgejump_key, &variables::config::movement::edgejump_key_type);
                if (variables::config::movement::edgejump)
                {
                    ImGui::Checkbox(xorstr("edge jump block buttons"), &variables::config::movement::edgejump_blockbuttons);
                }
                ImGui::Checkbox(xorstr("mini jump"), &variables::config::movement::minijump); ImGui::SameLine(); ImGui::KeyBind(xorstr("mini jump key"), &variables::config::movement::minijump_key, &variables::config::movement::minijump_key_type);
                if (variables::config::movement::minijump)
                {
                    ImGui::Checkbox(xorstr("mini jump force edgejump"), &variables::config::movement::minijump_forceedgejump);
                    ImGui::Checkbox(xorstr("mini jump block buttons"), &variables::config::movement::minijump_blockbuttons);
                }
                ImGui::Checkbox(xorstr("long jump"), &variables::config::movement::longjump); ImGui::SameLine(); ImGui::KeyBind(xorstr("long jump key"), &variables::config::movement::longjump_key, &variables::config::movement::minijump_key_type);
                if (variables::config::movement::longjump)
                {
                    ImGui::Checkbox(xorstr("long jump force edgejump"), &variables::config::movement::longjump_forceedgejump);
                    ImGui::Checkbox(xorstr("long jump block buttons"), &variables::config::movement::longjump_blockbuttons);
                }
                ImGui::Checkbox(xorstr("jump bug"), &variables::config::movement::jumpbug); ImGui::SameLine(); ImGui::KeyBind(xorstr("jump bug key"), &variables::config::movement::jumpbug_key, &variables::config::movement::jumpbug_key_type);
                ImGui::Checkbox(xorstr("auto duck"), &variables::config::movement::autoduck); ImGui::SameLine(); ImGui::KeyBind(xorstr("auto duck key"), &variables::config::movement::autoduck_key, &variables::config::movement::autoduck_key_type);
                if (variables::config::movement::autoduck)
                {
                    ImGui::SliderFloat(xorstr("auto duck time"), &variables::config::movement::autoduck_time, 0.00f, 1.00f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::Checkbox(xorstr("edge bug"), &variables::config::movement::edgebug); ImGui::SameLine(); ImGui::KeyBind(xorstr("edge bug key"), &variables::config::movement::edgebug_key, &variables::config::movement::edgebug_key_type);
                if (variables::config::movement::edgebug)
                {
                    ImGui::Combo(xorstr("edge bug style"), &variables::config::movement::edgebug_style_lock, "none\0dynamic\0full lock\0");
                    ImGui::Checkbox(xorstr("edge bug asist to edge/advanced detection"), &variables::config::movement::edgebug_strafetoedge);
                    ImGui::SliderInt(xorstr("edge bug ticks"), &variables::config::movement::edgebug_ticks, 0, 256, "%d", ImGuiSliderFlags_AlwaysClamp);
                    if (variables::config::movement::edgebug_style_lock == 1)
                    {
                        ImGui::SliderFloat(xorstr("edge bug strength lock"), &variables::config::movement::edgebug_lock, 1.0f, 100.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    }
                }
                ImGui::Checkbox(xorstr("auto align"), &variables::config::movement::autoalign); ImGui::SameLine(); ImGui::KeyBind(xorstr("auto align key"), &variables::config::movement::autoalign_key, &variables::config::movement::autoalign_key_type);
                ImGui::Checkbox(xorstr("auto pixel surf"), &variables::config::movement::pixelsurf); ImGui::SameLine(); ImGui::KeyBind(xorstr("auto pixel surf key"), &variables::config::movement::pixelsurf_key, &variables::config::movement::pixelsurf_key_type);
                ImGui::Checkbox(xorstr("mouse speed limit"), &variables::config::movement::msl); ImGui::SameLine(); ImGui::KeyBind(xorstr("mouse speed limiter key"), &variables::config::movement::msl_key, &variables::config::movement::msl_key_type);
                if (variables::config::movement::msl)
                {
                    ImGui::SliderFloat(xorstr("msl strength x"), &variables::config::movement::msl_strength_x, 0.0f, 100.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::SliderFloat(xorstr("msl strength y"), &variables::config::movement::msl_strength_y, 0.0f, 100.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::Checkbox(xorstr("stamina hop"), &variables::config::movement::staminahop); ImGui::SameLine(); ImGui::KeyBind(xorstr("stamina hop key"), &variables::config::movement::staminahop_key, &variables::config::movement::staminahop_key_type);
                if (variables::config::movement::staminahop)
                {
                    ImGui::SliderInt(xorstr("stamina hop ticks"), &variables::config::movement::staminahop_ticks, 0, 12, "%d", ImGuiSliderFlags_AlwaysClamp);
                }
                ImGui::Checkbox(xorstr("infinity duck"), &variables::config::movement::infinityduck);
                if (ImGui::BeginCombo(xorstr("block buttons"), xorstr("select"), ImGuiComboFlags_NoArrowButton))
                {
                    ImGui::Selectable(xorstr("forward"), &variables::config::movement::blockbutton_forward, ImGuiSelectableFlags_DontClosePopups);
                    ImGui::Selectable(xorstr("back"), &variables::config::movement::blockbutton_back, ImGuiSelectableFlags_DontClosePopups);
                    ImGui::Selectable(xorstr("left"), &variables::config::movement::blockbutton_left, ImGuiSelectableFlags_DontClosePopups);
                    ImGui::Selectable(xorstr("right"), &variables::config::movement::blockbutton_right, ImGuiSelectableFlags_DontClosePopups);

                    ImGui::EndCombo();
                }
                ImGui::Checkbox(xorstr("jump stats"), &variables::config::movement::jumpstats);
            }
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::BeginChild(xorstr("settings"), misc_group_size, true);
            {
                static int config_index = -1;
                static char buffer[10];

                ImGui::InputTextWithHint(xorstr("##config name"), xorstr("config name"), buffer, sizeof(buffer));

                if (ImGui::BeginCombo(xorstr(" "), config_index != -1 ? configsystem::get().configs.at(config_index).c_str() : "configs", ImGuiComboFlags_NoArrowButton))
                {
                    const std::vector<std::string>& configs_vector = configsystem::get().configs;

                    for (std::size_t i = 0u; i < configs_vector.size(); ++i)
                    {
                        std::string const& config_name = configs_vector[i].data();

                        if (ImGui::Selectable(config_name.c_str(), i == config_index))
                        {
                            config_index = i;
                        }
                    }

                    ImGui::EndCombo();
                }
                ImGui::SameLine();
                if (ImGui::Button(xorstr("refresh")))
                {
                    configsystem::get().update_configs();
                    notify::get().run(xorstr("refreshed config list"), true, true, true);
                }

                ImGui::Spacing();
                if (ImGui::Button(xorstr("create")))
                {
                    configsystem::get().create_file(buffer);
                    notify::get().run(xorstr("created config"), true, true, true);
                }

                if (config_index != -1 && config_index < static_cast<int>(configsystem::get().configs.size()))
                {
                    ImGui::SameLine();

                    if (ImGui::Button(xorstr("save")))
                    {
                        configsystem::get().save(config_index);
                        notify::get().run(xorstr("saved config"), true, true, true);
                    }
                    ImGui::SameLine();

                    if (ImGui::Button(xorstr("load")))
                    {
                        configsystem::get().load(config_index);
                        notify::get().run(xorstr("loaded config"), true, true, true);
                    }
                    ImGui::SameLine();

                    if (ImGui::Button(xorstr("delete")))
                    {
                        configsystem::get().delete_file(config_index);
                        notify::get().run(xorstr("deleted config"), true, true, true);
                    }
                }

                ImGui::Spacing();

                if (ImGui::Button(xorstr("open config folder")))
                {
                    ShellExecute(0, 0, "weiamware", 0, 0, SW_SHOW);
                }
                ImGui::SameLine();

                if (ImGui::Button(xorstr("unload")))
                {
                    variables::hack::unload = true;
                }
            }
            ImGui::EndChild();
            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        }
    }
    ImGui::End();
    ImGui::PopStyleColor(11);
    ImGui::PopStyleVar(6); */
}

void menu::release()
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
}

bool menu::colorpicker(const char* label, color* v)
{
    float clr[4] = {
        v->get_red() / 255.0f,
        v->get_green() / 255.0f,
        v->get_blue() / 255.0f,
        v->get_alpha() / 255.0f
    };

    if (ImGui::ColorEdit4(label, clr, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_AlphaBar))
    {
        v->set(clr[0], clr[1], clr[2], clr[3]);
        return true;
    }

    return false;
}

bool menu::checkbox(const char* name, bool* check)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(name);
    const ImVec2 label_size = ImGui::CalcTextSize(name, NULL, true);

    const float square_sz = ImGui::GetFrameHeight();
    const ImVec2 pos = window->DC.CursorPos;
    const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));

    ImGui::ItemSize(total_bb, style.FramePadding.y);

    if (!ImGui::ItemAdd(total_bb, id))
    {
        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
        return false;
    }

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
    if (pressed)
    {
        *check = !(*check);
        ImGui::MarkItemEdited(id);
    }

    static std::map<ImGuiID, float> map_animation;

    auto animation = map_animation.find(id);

    if (animation == map_animation.end())
    {
        float value = 0.0f;
        map_animation.insert({ id, value });
        animation = map_animation.find(id);
    }

    animation->second = ImLerp(animation->second, (*check ? 1.f : 0.f), g.IO.DeltaTime * 5.0f);

    auto bg_checkmarker_color = ImLerp(ImColor(0.10f, 0.08f, 0.11f, 1.0f), ImColor(0.16f, 0.14f, 0.18f, 1.0f), animation->second);
    auto text_checkmarker_color = ImLerp(ImColor(180, 180, 180, 200), ImColor(255, 255, 255, 255), animation->second);
    auto checkmarker_color = ImLerp(ImColor(0.249f, 0.167f, 0.334f, 1.0f), ImColor(0.349f, 0.267f, 0.434f, 1.0f), animation->second);

    const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));

    ImGui::RenderNavHighlight(total_bb, id);
    ImGui::RenderFrame(ImVec2(check_bb.Min.x + 2, check_bb.Min.y), check_bb.Max, bg_checkmarker_color/*ImGui::GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg)*/, false, 5.5f /*style.FrameRounding*/);

    bool mixed_value = (g.LastItemData.InFlags & ImGuiItemFlags_MixedValue) != 0;

    if (mixed_value)
    {
        ImVec2 pad(ImMax(1.0f, IM_FLOOR(square_sz / 3.6f)), ImMax(1.0f, IM_FLOOR(square_sz / 3.6f)));

        window->DrawList->AddRectFilled(check_bb.Min + pad, check_bb.Max - pad, ImColor(0.0f, 0.0f, 0.0f), style.FrameRounding);
    }
    else if (*check)
    {
        const float pad = ImMax(1.0f, IM_FLOOR(square_sz / 5.0f));
        ImGui::RenderCheckMark(window->DrawList, ImVec2(check_bb.Min.x + 1, check_bb.Min.y) + ImVec2(pad, pad), checkmarker_color, square_sz - pad * 2.0f);
    }

    ImVec2 label_pos = ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y);

    if (g.LogEnabled)
        ImGui::LogRenderedText(&label_pos, mixed_value ? "[~]" : *check ? "[x]" : "[ ]");

    if (label_size.x > 0.0f)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(text_checkmarker_color));
        ImGui::RenderText(label_pos, name);
        ImGui::PopStyleColor();
    }

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));

    return pressed;
}

bool menu::tab(const char* name, bool select_check)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();

    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(name);
    const ImVec2 label_size = ImGui::CalcTextSize(name, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    auto tab_size = ImVec2(5 + label_size.x, 5 + label_size.y);
    ImVec2 size = ImGui::CalcItemSize(tab_size, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
    const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));

    ImGui::ItemSize(size, style.FramePadding.y);

    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);

    static std::map<ImGuiID, float> map_animation;

    auto animation = map_animation.find(id);

    if (animation == map_animation.end())
    {
        float value = 0.0f;
        map_animation.insert({ id, value });
        animation = map_animation.find(id);
    }

    animation->second = ImClamp(animation->second + (5.0f * g.IO.DeltaTime * (select_check ? 1.f : -1.f)), 0.0f, 1.0f);

    auto checkmarker_color = ImLerp(ImColor(1.0f, 1.0f, 1.0f, 0.2f), ImColor(0.349f, 0.267f, 0.434f, 1.0f), animation->second);

    window->DrawList->AddText(ImVec2(bb.Min.x + size.x / 2 - ImGui::CalcTextSize(name).x / 2, bb.Min.y + size.y / 2 - ImGui::CalcTextSize(name).y / 2), checkmarker_color, name);

    return pressed;
}

bool menu::button(const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
        pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
    ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, pos + size);
    ImGui::ItemSize(size, style.FramePadding.y);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

    static std::map<ImGuiID, float> map_animation;

    auto animation = map_animation.find(id);

    if (animation == map_animation.end())
    {
        float alpha = 0.0f;
        map_animation.insert({ id, alpha });
        animation = map_animation.find(id);
    }

    animation->second = ImLerp(animation->second, ((held && hovered) ? 1.f : 0.f), g.IO.DeltaTime * 1.55f * 5.0f);

    auto button_color = ImLerp(ImColor(0.217f, 0.188f, 0.247f, 1.0f), ImColor(0.349f, 0.267f, 0.434f, 1.0f), animation->second);

    ImGui::RenderNavHighlight(bb, id);
    ImGui::RenderFrame(bb.Min, bb.Max, button_color, false, style.FrameRounding);

    if (g.LogEnabled)
        ImGui::LogSetNextTextDecoration("[", "]");

    ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);

    // Automatically close popups
    //if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
    //    CloseCurrentPopup();

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
    return pressed;
}

bool menu::exslider(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();

    ImGuiContext& g = *GImGui;
    ImGuiStyle& style = g.Style;
    ImGuiID id = window->GetID(label);

    const float width = ImGui::GetWindowWidth();

    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
    const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(width, label_size.y + style.FramePadding.y * 2.0f));
    const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

    ImGui::ItemAdd(total_bb, id);
    ImGui::ItemSize(total_bb, style.FramePadding.y);

    // Default format string when passing NULL
    if (format == NULL)
        format = ImGui::DataTypeGetInfo(data_type)->PrintFmt;

    const bool hovered = ImGui::ItemHoverable(frame_bb, id, 0);
    const bool clicked = hovered && ImGui::IsMouseClicked(0, id);

    if (clicked)
    {
        ImGui::SetActiveID(id, window);
        ImGui::SetFocusID(id, window);
        ImGui::FocusWindow(window);
        g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
    }

    // Slider behavior
    ImRect grab_bb;
    const bool value_changed = ImGui::SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, flags, &grab_bb);

    if (value_changed)
        ImGui::MarkItemEdited(id);

    struct anim
    {
        float smooth;
        float alpha;
    };

    static std::map<ImGuiID, anim> map_animation;

    auto animation = map_animation.find(id);

    if (animation == map_animation.end())
    {
        map_animation.insert({ id, { 0.0f, 0.0f } });
        animation = map_animation.find(id);
    }
    animation->second.smooth = ImLerp(animation->second.smooth, grab_bb.Min.x - frame_bb.Min.x, g.IO.DeltaTime * 5.0f);
    animation->second.alpha = ImClamp(animation->second.alpha + (5.0f * g.IO.DeltaTime * (hovered ? 1.f : -1.f)), 0.0f, 1.0f);

    char value_buf[64];
    const char* value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);

    auto bg_slider_color = ImLerp(ImColor(0.10f, 0.08f, 0.11f, 1.0f), ImColor(0.16f, 0.14f, 0.18f, 1.0f), animation->second.alpha);
    auto filled_bg_color = ImLerp(ImColor(1.0f, 1.0f, 1.0f, 0.2f), ImColor(0.349f, 0.267f, 0.434f, 1.0f), animation->second.alpha);
    auto text_slider_color = ImLerp(ImColor(180, 180, 180, 200), ImColor(255, 255, 255, 255), animation->second.alpha);

    window->DrawList->AddText(ImVec2(frame_bb.Min.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y - 5), text_slider_color, label);
    window->DrawList->AddText(ImVec2((frame_bb.Max.x - ImGui::CalcTextSize(value_buf, value_buf_end).x) - style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y - 5), text_slider_color, value_buf);
    window->DrawList->AddRectFilled(ImVec2(frame_bb.Min.x + style.ItemInnerSpacing.x, frame_bb.Min.y + 20), ImVec2(frame_bb.Max.x - style.ItemInnerSpacing.x, (frame_bb.Max.y - style.FramePadding.y) + 5), bg_slider_color, 5);
    window->DrawList->AddRectFilled(ImVec2(frame_bb.Min.x + style.ItemInnerSpacing.x, frame_bb.Min.y + 20), ImVec2(frame_bb.Min.x + style.ItemInnerSpacing.x + animation->second.smooth + 12, (frame_bb.Max.y - style.FramePadding.y) + 5), filled_bg_color, 5);
    window->DrawList->AddRectFilled(ImVec2((frame_bb.Min.x + style.ItemInnerSpacing.x) + animation->second.smooth - 10, frame_bb.Min.y + 18), ImVec2(frame_bb.Min.x + style.ItemInnerSpacing.x + 4 + animation->second.smooth + 10, (frame_bb.Max.y - style.FramePadding.y) + 8), bg_slider_color, 3);

    return value_changed;
}

bool menu::sliderint(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
    return exslider(label, ImGuiDataType_S32, v, &v_min, &v_max, format, flags);
}

bool menu::sliderfloat(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
    return exslider(label, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);
}

static ImVec2 CalcWindowSizeAfterConstraint(ImGuiWindow* window, ImVec2 new_size)
{
    ImGuiContext& g = *GImGui;
    if (g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSizeConstraint)
    {
        // Using -1,-1 on either X/Y axis to preserve the current size.
        ImRect cr = g.NextWindowData.SizeConstraintRect;
        new_size.x = (cr.Min.x >= 0 && cr.Max.x >= 0) ? ImClamp(new_size.x, cr.Min.x, cr.Max.x) : window->SizeFull.x;
        new_size.y = (cr.Min.y >= 0 && cr.Max.y >= 0) ? ImClamp(new_size.y, cr.Min.y, cr.Max.y) : window->SizeFull.y;
        if (g.NextWindowData.SizeCallback)
        {
            ImGuiSizeCallbackData data;
            data.UserData = g.NextWindowData.SizeCallbackUserData;
            data.Pos = window->Pos;
            data.CurrentSize = window->SizeFull;
            data.DesiredSize = new_size;
            g.NextWindowData.SizeCallback(&data);
            new_size = data.DesiredSize;
        }
        new_size.x = IM_FLOOR(new_size.x);
        new_size.y = IM_FLOOR(new_size.y);
    }

    // Minimum size
    if (!(window->Flags & (ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_AlwaysAutoResize)))
    {
        ImGuiWindow* window_for_height = window;
        new_size = ImMax(new_size, g.Style.WindowMinSize);
        new_size.y = ImMax(new_size.y, window_for_height->TitleBarHeight() + window_for_height->MenuBarHeight() + ImMax(0.0f, g.Style.WindowRounding - 1.0f)); // Reduce artifacts with very small windows
    }
    return new_size;
}

static ImVec2 CalcWindowContentSize(ImGuiWindow* window)
{
    if (window->Collapsed)
        if (window->AutoFitFramesX <= 0 && window->AutoFitFramesY <= 0)
            return window->ContentSize;
    if (window->Hidden && window->HiddenFramesCannotSkipItems == 0 && window->HiddenFramesCanSkipItems > 0)
        return window->ContentSize;

    ImVec2 sz;
    sz.x = IM_FLOOR((window->ContentSizeExplicit.x != 0.0f) ? window->ContentSizeExplicit.x : window->DC.CursorMaxPos.x - window->DC.CursorStartPos.x);
    sz.y = IM_FLOOR((window->ContentSizeExplicit.y != 0.0f) ? window->ContentSizeExplicit.y : window->DC.CursorMaxPos.y - window->DC.CursorStartPos.y);
    return sz;
}

static ImVec2 CalcWindowAutoFitSize(ImGuiWindow* window, const ImVec2& size_contents)
{
    ImGuiContext& g = *GImGui;
    ImGuiStyle& style = g.Style;
    ImVec2 size_decorations = ImVec2(0.0f, window->TitleBarHeight() + window->MenuBarHeight());
    ImVec2 size_pad = window->WindowPadding * 2.0f;
    ImVec2 size_desired = size_contents + size_pad + size_decorations;
    if (window->Flags & ImGuiWindowFlags_Tooltip)
    {
        // Tooltip always resize
        return size_desired;
    }
    else
    {
        // Maximum window size is determined by the viewport size or monitor size
        const bool is_popup = (window->Flags & ImGuiWindowFlags_Popup) != 0;
        const bool is_menu = (window->Flags & ImGuiWindowFlags_ChildMenu) != 0;
        ImVec2 size_min = style.WindowMinSize;
        if (is_popup || is_menu) // Popups and menus bypass style.WindowMinSize by default, but we give then a non-zero minimum size to facilitate understanding problematic cases (e.g. empty popups)
            size_min = ImMin(size_min, ImVec2(4.0f, 4.0f));
        ImVec2 size_auto_fit = ImClamp(size_desired, size_min, ImMax(size_min, g.IO.DisplaySize - style.DisplaySafeAreaPadding * 2.0f));

        // When the window cannot fit all contents (either because of constraints, either because screen is too small),
        // we are growing the size on the other axis to compensate for expected scrollbar. FIXME: Might turn bigger than ViewportSize-WindowPadding.
        ImVec2 size_auto_fit_after_constraint = CalcWindowSizeAfterConstraint(window, size_auto_fit);
        bool will_have_scrollbar_x = (size_auto_fit_after_constraint.x - size_pad.x - size_decorations.x < size_contents.x && !(window->Flags & ImGuiWindowFlags_NoScrollbar) && (window->Flags & ImGuiWindowFlags_HorizontalScrollbar)) || (window->Flags & ImGuiWindowFlags_AlwaysHorizontalScrollbar);
        bool will_have_scrollbar_y = (size_auto_fit_after_constraint.y - size_pad.y - size_decorations.y < size_contents.y && !(window->Flags & ImGuiWindowFlags_NoScrollbar)) || (window->Flags & ImGuiWindowFlags_AlwaysVerticalScrollbar);
        if (will_have_scrollbar_x)
            size_auto_fit.y += style.ScrollbarSize;
        if (will_have_scrollbar_y)
            size_auto_fit.x += style.ScrollbarSize;
        return size_auto_fit;
    }
}

ImVec2 CalcWindowExpectedSize(ImGuiWindow* window)
{
    ImVec2 size_contents = CalcWindowContentSize(window);
    ImVec2 size_auto_fit = CalcWindowAutoFitSize(window, size_contents);
    ImVec2 size_final = CalcWindowSizeAfterConstraint(window, size_auto_fit);
    return size_final;
}

static ImRect GetViewportRect()
{
    ImGuiContext& g = *GImGui;
    return ImRect(0.0f, 0.0f, g.IO.DisplaySize.x, g.IO.DisplaySize.y);
}

ImRect GetWindowAllowedExtentRect(ImGuiWindow* window)
{
    IM_UNUSED(window);
    ImVec2 padding = GImGui->Style.DisplaySafeAreaPadding;
    ImRect r_screen = GetViewportRect();
    r_screen.Expand(ImVec2((r_screen.GetWidth() > padding.x * 2) ? -padding.x : 0.0f, (r_screen.GetHeight() > padding.y * 2) ? -padding.y : 0.0f));
    return r_screen;
}

bool menu::keybind(const char* label, int* k, int* key_style)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    ImGuiIO& io = g.IO;
    const ImGuiStyle& style = g.Style;

    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
    auto tab_size = ImVec2(5 + label_size.x, 5 + label_size.y);
    ImVec2 size = ImGui::CalcItemSize(tab_size, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
    const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + size);
    const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

    ImGui::ItemSize(total_bb, style.FramePadding.y);
    if (!ImGui::ItemAdd(total_bb, id))
        return false;

    const bool focus_requested = ImGui::FocusableItemRegister(window, g.ActiveId == id);
    const bool hovered = ImGui::ItemHoverable(frame_bb, id, ImGuiItemFlags_None);
    const bool user_clicked = hovered && io.MouseClicked[0];
    const bool user_rightclicked = hovered && io.MouseClicked[1];

    if (hovered)
    {
        ImGui::SetHoveredID(id);
        g.MouseCursor = ImGuiMouseCursor_TextInput;
    }

    if (focus_requested || user_clicked)
    {
        if (g.ActiveId != id)
        {
            memset(io.MouseDown, 0, sizeof(io.MouseDown));
            memset(io.KeysDown, 0, sizeof(io.KeysDown));
            *k = 0;
        }

        ImGui::SetActiveID(id, window);
        ImGui::FocusWindow(window);
    }
    else if (io.MouseClicked[0])
    {
        if (g.ActiveId == id)
        {
            ImGui::ClearActiveID();
        }
    }

    bool value_changed = false;
    int key = *k;

    if (g.ActiveId == id) {
        for (auto i = 0; i < 5; i++) {
            if (io.MouseDown[i]) {
                switch (i) {
                case 0:
                    key = VK_LBUTTON;
                    break;
                case 1:
                    key = VK_RBUTTON;
                    break;
                case 2:
                    key = VK_MBUTTON;
                    break;
                case 3:
                    key = VK_XBUTTON1;
                    break;
                case 4:
                    key = VK_XBUTTON2;
                    break;
                }
                value_changed = true;
                ImGui::ClearActiveID();
            }
        }
        if (!value_changed) {
            for (auto i = VK_BACK; i <= VK_RMENU; i++) {
                if (io.KeysDown[i]) {
                    key = i;
                    value_changed = true;
                    ImGui::ClearActiveID();
                }
            }
        }

        if (ImGui::IsKeyPressedMap(ImGuiKey_Escape)) {
            *k = 0;
            ImGui::ClearActiveID();
        }
        else {
            *k = key;
        }
    }
    else {
        bool popup_open = ImGui::IsPopupOpen(id, ImGuiPopupFlags_None);
        if (user_rightclicked && !popup_open && *key_style > 0)
            ImGui::OpenPopupEx(id);

        if (popup_open) {
            char name[16];
            ImFormatString(name, IM_ARRAYSIZE(name), "##Combo_%02d", g.BeginPopupStack.Size);

            if (ImGuiWindow* popup_window = ImGui::FindWindowByName(name))
                if (popup_window->WasActive)
                {
                    ImVec2 size_expected = CalcWindowExpectedSize(popup_window);
                    ImRect r_outer = GetWindowAllowedExtentRect(popup_window);
                    ImVec2 pos = ImGui::FindBestWindowPosForPopupEx(frame_bb.GetBL(), size_expected, &popup_window->AutoPosLastDirection, r_outer, frame_bb, ImGuiPopupPositionPolicy_ComboBox);
                    ImGui::SetNextWindowPos(pos);
                }

            ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_Popup | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(style.FramePadding.x, style.WindowPadding.y));
            bool ret = ImGui::Begin(name, NULL, window_flags);
            ImGui::PopStyleVar();

            if (ImGui::Selectable("always", *key_style == 1))
            {
                *key_style = 1;
            }

            if (ImGui::Selectable("hold", *key_style == 2))
            {
                *key_style = 2;
            }

            if (ImGui::Selectable("toggle", *key_style == 3))
            {
                *key_style = 3;
            }

            if (ImGui::Selectable("off key", *key_style == 4))
            {
                *key_style = 4;
            }

            ImGui::EndPopup();
        }

    }

    char buf_display[64] = "key";
    ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), false, style.FrameRounding);

    if (*k != 0 && g.ActiveId != id) {
        strcpy_s(buf_display, KeyNames[*k]);
    }
    else if (g.ActiveId == id) {
        strcpy_s(buf_display, "press");
    }

    const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y);
    ImGui::RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, style.ButtonTextAlign, &clip_rect);

    return value_changed;
}