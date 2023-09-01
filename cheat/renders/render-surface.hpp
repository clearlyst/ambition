#pragma once
#include "../helpers/xor.hpp"
#include "../valve_sdk/sdk.hpp"
#include "../helpers/singleton.hpp"
#include "../valve_sdk/misc/Color.hpp"

enum font_flags 
{
	fontflag_none,
	fontflag_italic = 0x001,
	fontflag_underline = 0x002,
	fontflag_strikeout = 0x004,
	fontflag_symbol = 0x008,
	fontflag_antialias = 0x010,
	fontflag_gaussianblur = 0x020,
	fontflag_rotary = 0x040,
	fontflag_dropshadow = 0x080,
	fontflag_additive = 0x100,
	fontflag_outline = 0x200,
	fontflag_custom = 0x400,
	fontflag_bitmap = 0x800,
};

namespace fonts
{
	extern unsigned long font;
}

class surfacerender : public singleton<surfacerender>
{
public:
	void initialize();

	void draw_line(std::int32_t from_x, std::int32_t from_y, std::int32_t to_x, std::int32_t to_y, color color);
	void draw_text(std::int32_t x, std::int32_t y, unsigned long font, const wchar_t* text, bool centered, color color);
	void draw_text(std::int32_t x, std::int32_t y, unsigned long font, std::string text, bool centered, color color);
	void draw_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color);
	void draw_filled_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color);
	void draw_rect_fade_vertical(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color top, color bottom);
	void draw_rect_fade_horizontal(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color left, color right);
	void draw_outline(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color);
	void draw_textured_polygon(std::int32_t vertices_count, Vertex_t* vertices, color color);
	void draw_circle(std::int32_t x, std::int32_t y, std::int32_t radius, std::int32_t segments, color color);
	void draw_circle_filled(std::int32_t x, std::int32_t y, std::int32_t points, std::int32_t radius, color color);
	void draw_corner_box(int x, int y, int w, int h, color color);

	Vector2D get_text_size(unsigned long font, std::string text);
};