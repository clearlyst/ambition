#pragma once

class IPanel
{
public:
    void set_keyboard_input_enabled(unsigned int panel_id, bool state)
    {
        using original_fn = void(__thiscall*)(IPanel*, unsigned int, bool);
        return (*(original_fn**)this)[31](this, panel_id, state);
    }

    void set_mouse_input_enabled(unsigned int panel_id, bool state)
    {
        using original_fn = void(__thiscall*)(IPanel*, unsigned int, bool);
        return (*(original_fn**)this)[32](this, panel_id, state);
    }

    const char* get_panel_name(unsigned int panel_id) 
    {
        using original_fn = const char* (__thiscall*)(IPanel*, unsigned int);
        return (*(original_fn**)this)[36](this, panel_id);
    }

#ifdef GetClassName
#undef GetClassName
#endif
    const char *GetClassName(unsigned int vguiPanel)
    {
        typedef const char *(__thiscall* tGetClassName)(void*, unsigned int);
        return CallVFunction<tGetClassName>(this, 37)(this, vguiPanel);
    }
};
