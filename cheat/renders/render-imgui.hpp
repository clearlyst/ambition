#pragma once
#include <functional>
#include <deque>
#include <any>
#include <mutex>
#include <shared_mutex>

#include "../features/esp/esp.hpp"
#include "../features/misc/misc.hpp"
#include "../features/indicators/indicators.hpp"
#include "../features/notifications/notifications.hpp"

#include "../menu.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_freetype.h"

#include "../helpers/xor.hpp"
#include "../helpers/input.hpp"
#include "../valve_sdk/sdk.hpp"
#include "../helpers/singleton.hpp"
#include "../valve_sdk/misc/Color.hpp"

enum DrawObjectType : int 
{
	DrawObject_NONE = 0,
	DrawObject_LINE = 1,
	DrawObject_RECT = 2,
	DrawObject_TEXT = 3,
	DrawObject_RECTMULTI = 4,
	DrawObject_CIRCLE3D = 5,
	DrawObject_CIRCLE2D = 6,
	DrawObject_CIRCLE2DFiled = 7,
	DrawObject_Arc = 8,
	DrawObject_Triangle = 9,
	DrawObject_TriangleFilled = 10,
};

enum RectType_t : int
{
	RectType_Clear = 0,
	RectType_Filled = 1,
};

struct TriangleObject_t
{
	ImVec2 m_Min{ };
	ImVec2 m_Mun{ };
	ImVec2 m_Max{ };
	color m_Color{ };
	float m_fThickness = 1.f;
};

struct TriangleFilledObject_t
{
	ImVec2 m_Min{ };
	ImVec2 m_Mun{ };
	ImVec2 m_Max{ };
	color m_Color{ };
};

struct LineObject_t
{
	ImVec2 m_Min{ };
	ImVec2 m_Max{ };
	color m_Color{ };
	float m_fThickness = 0.f;
};

struct RectObject_t
{
	ImVec2 m_Min{ };
	ImVec2 m_Max{ };
	color m_Color{ };
	float m_fThickness = 1.f;
	float m_fRounding = 0.f;
	ImDrawCornerFlags m_tCorners = ImDrawCornerFlags_None;
	RectType_t m_RectType = RectType_Clear;
};

struct RectMultiObject_t
{
	ImVec2 m_Min{ };
	ImVec2 m_Max{ };
	color m_Color1{ };
	color m_Color2{ };
	color m_Color3{ };
	color m_Color4{ };
};

struct TextObject_t
{
	ImFont* m_Font = nullptr;
	float m_fFontSize = 14.0f;
	ImVec2 m_Pos{ };
	std::string m_Text;
	color m_Color{ };
	color m_Color_outline{ };
	bool Outline = false;
	bool Dropshadow = false;
	bool Center = false;
	bool Right = false;
};

struct Circle3dObject_t
{
	Vector Pos{ };
	float Points = 16;
	color Color{ };
	float Radius = 0.f;
};

struct ArcObject_t
{
	ImVec2 Pos{ };
	float Radius = 16;
	float MinAngle = 0.f;
	float MaxAngle = 0.f;
	color Color;
	float Thikness;
};

struct DrawQueueObject_t
{
	DrawQueueObject_t(const DrawObjectType type, std::any&& object) : m_Type(type), m_Object(object) {};

	DrawObjectType m_Type;
	std::any m_Object;
};

extern ImFont* titlemenufont;
extern ImFont* textmenufont;
extern ImFont* iconmenufont;
extern ImFont* indicatorsfont;
extern ImFont* screenmessagefont;
extern ImFont* firstespfont;
extern ImFont* secondespfont;
extern ImFont* weaponiconfont;
extern ImFont* screenmiscfont;


/*
extern ImFont* menufont;
extern ImFont* menutextfont;
extern ImFont* espfontfirstfont;
extern ImFont* espfontsecondfont;
extern ImFont* indicatorsbigfont;
extern ImFont* screenmessage;
extern ImFont* espfonticon;
extern ImFont* spectatorlistiwebzfontname;
extern ImFont* spectatorlistiwebzfontspectators;
*/

class imguirender : public singleton<imguirender>
{
public:
	static ImU32 getU32(color color)
	{
		return ((color[3] & 0xff) << 24) + ((color[2] & 0xff) << 16) + ((color[1] & 0xff) << 8) + (color[0] & 0xff);
	}
public:
	virtual void Instance();
	virtual void SetupData();
	virtual void SwapDrawData();
	virtual void ClearDrawData();

	// renderer functions
	virtual void AddLine(ImVec2 min, ImVec2 max, color clr, float thickness = 1.0f);
	virtual void AddRect(ImVec2 min, ImVec2 max, color clr, float thickness = 1, float rounding = 0, ImDrawCornerFlags corners = ImDrawCornerFlags_None);
	virtual void AddRectFilled(ImVec2 min, ImVec2 max, color clr, float rounding = 0, ImDrawCornerFlags corners = ImDrawCornerFlags_None);
	virtual void AddRectFilledMultiColor(ImVec2 min, ImVec2 max, color col, color col2, color col3, color col4);
	virtual void AddText(ImFont* font, float font_size, ImVec2 pos, std::string text, color clr, color clr_outline, bool outline, bool dropshadow, bool center = false, bool right = false);
	virtual void AddCircle3D(Vector position, float points, float radius, color color);
	virtual void AddCircle2D(Vector position, float points, float radius, color color);
	virtual void AddCircle2DFilled(Vector position, float points, float radius, color color);
	virtual void AddArc(ImVec2 position, float radius, float min_angle, float max_angle, color col, float thickness);
	virtual void AddTriangle(ImVec2 position1, ImVec2 position2, ImVec2 position3, color clr, float thickness = 1.0f);
	virtual void AddTriangleFilled(ImVec2 position1, ImVec2 position2, ImVec2 position3, color clr);

	HWND m_HWND = NULL;
private:
	// draw list queue
	std::deque< DrawQueueObject_t > m_DrawListQueue;
	std::deque< DrawQueueObject_t > m_DrawListQueueSafe;

	// shared mtx
	std::shared_mutex m_DrawMutex = { };
};