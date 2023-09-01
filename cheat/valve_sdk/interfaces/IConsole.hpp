#include <stdint.h>
#include "IConVar.hpp"
#include "IAppSystem.hpp"

class i_console;
class convar;
class con_command;
class con_command_base;

typedef int cvar_dll_indentifier_t;

class i_console_display_func {
public:
	virtual void color_print(const uint8_t* clr, const char* msg) = 0;
	virtual void print(const char* msg) = 0;
	virtual void drint(const char* msg) = 0;
};

struct _color {
	unsigned char r, g, b, a;
};

class i_console : public IAppSystem {
public:
	virtual cvar_dll_indentifier_t allocate_dll_indentifier() = 0;
	virtual void register_con_command(con_command_base* base) = 0;
	virtual void unregister_con_command(con_command_base* base) = 0;
	virtual void unregister_con_commands(cvar_dll_indentifier_t id) = 0;
	virtual const char* get_command_line_value(const char* name) = 0;
	virtual con_command_base* find_command_base(const char* name) = 0;
	virtual const con_command_base* find_command_base(const char* name) const = 0;
	virtual convar* get_convar(const char* var_name) = 0;
	virtual const convar* get_convar(const char* var_name) const = 0;
	virtual con_command* find_command(const char* name) = 0;
	virtual const con_command* find_command(const char* name) const = 0;
	virtual void install_global_change_callback(FnChangeCallback_t callback) = 0;
	virtual void remove_global_change_callback(FnChangeCallback_t callback) = 0;
	virtual void call_global_change_callbacks(convar* var, const char* old_str, float old_val) = 0;
	virtual void install_console_display_func(i_console_display_func* func) = 0;
	virtual void remove_console_display_func(i_console_display_func* func) = 0;
	virtual void console_color_printf(const _color& clr, const char* format, ...) const = 0;
	virtual void console_printf(const char* format, ...) const = 0;
	virtual void dconsole_dprintf(const char* format, ...) const = 0;
	virtual void rever_flagged_convars(int flag) = 0;
};

class CHudChat
{
public:
	enum ChatFilters
	{
		CHAT_FILTER_NONE = 0,
		CHAT_FILTER_JOINLEAVE = 0x000001,
		CHAT_FILTER_NAMECHANGE = 0x000002,
		CHAT_FILTER_PUBLICCHAT = 0x000004,
		CHAT_FILTER_SERVERMSG = 0x000008,
		CHAT_FILTER_TEAMCHANGE = 0x000010,
		CHAT_FILTER_ACHIEVEMENT = 0x000020,
	};

	void chat_printf(int iPlayerIndex, int iFilter, const char* fmt, ...)
	{
		char msg[1024];
		va_list args;
		va_start(args, fmt);
		vsprintf(msg, fmt, args);
		CallVFunction<void(__cdecl*)(void*, int, int, const char*, ...)>(this, 27)(this, iPlayerIndex, iFilter, fmt);
		va_end(args);
	}
};

class i_localize
{
public:
	wchar_t* find(const char* token_name) 
	{
		using original_fn = wchar_t* (__thiscall*)(i_localize*, const char*);
		return (*(original_fn**)this)[12](this, token_name);
	}
};
