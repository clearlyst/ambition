#include "render-surface.hpp"

unsigned long fonts::font;

void surfacerender::initialize()
{
	fonts::font = g_VGuiSurface->font_create();

	g_VGuiSurface->set_font_glyph(fonts::font, xorstr("Tahoma"), 12, 300, 0, 0, font_flags::fontflag_dropshadow);

	console::get().log(xorstr("weiamware | surface render font(s) initialized\n"));
}

void surfacerender::draw_line(std::int32_t x1, std::int32_t y1, std::int32_t x2, std::int32_t y2, color color)
{
	g_VGuiSurface->set_drawing_color(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
	g_VGuiSurface->draw_line(x1, y1, x2, y2);
}

void surfacerender::draw_text(std::int32_t x, std::int32_t y, unsigned long font, const wchar_t* text, bool centered, color color)
{
	g_VGuiSurface->draw_text_font(font);

	int text_width, text_height;

	if (centered)
	{
		g_VGuiSurface->get_text_size(font, text, text_width, text_height);
		g_VGuiSurface->draw_text_pos(x - text_width / 2, y);
	}
	else
	{
		g_VGuiSurface->draw_text_pos(x, y);
	}

	g_VGuiSurface->set_text_color(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
	g_VGuiSurface->draw_render_text(text, wcslen(text));
}

void surfacerender::draw_text(std::int32_t x, std::int32_t y, unsigned long font, std::string text, bool centered, color color)
{
	wchar_t temp[128];
	int text_width, text_height;

	if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, temp, 128) > 0)
	{
		g_VGuiSurface->draw_text_font(font);

		if (centered) 
		{
			g_VGuiSurface->get_text_size(font, temp, text_width, text_height);
			g_VGuiSurface->draw_text_pos(x - text_width / 2, y);
		}
		else
		{
			g_VGuiSurface->draw_text_pos(x, y);
		}

		g_VGuiSurface->set_text_color(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
		g_VGuiSurface->draw_render_text(temp, wcslen(temp));
	}
}

void surfacerender::draw_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color)
{
	g_VGuiSurface->set_drawing_color(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
	g_VGuiSurface->draw_outlined_rect(x, y, width, height);
}

void surfacerender::draw_filled_rect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color)
{
	g_VGuiSurface->set_drawing_color(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
	g_VGuiSurface->draw_filled_rectangle(x, y, width, height);
}

void surfacerender::draw_rect_fade_vertical(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color top, color bottom) 
{
	g_VGuiSurface->set_drawing_color(top.get_red(), top.get_green(), top.get_blue(), top.get_alpha());
	g_VGuiSurface->draw_filled_rect_fade(x, y, width, height, 255, 255, false);

	g_VGuiSurface->set_drawing_color(bottom.get_red(), bottom.get_green(), bottom.get_blue(), bottom.get_alpha());
	g_VGuiSurface->draw_filled_rect_fade(x, y, width, height, 0, 255, false);
}

void surfacerender::draw_rect_fade_horizontal(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color left, color right) 
{
	g_VGuiSurface->set_drawing_color(left.get_red(), left.get_green(), left.get_blue(), left.get_alpha());
	g_VGuiSurface->draw_filled_rect_fade(x, y, width, height, 255, 255, true);

	g_VGuiSurface->set_drawing_color(right.get_red(), right.get_green(), right.get_blue(), right.get_alpha());
	g_VGuiSurface->draw_filled_rect_fade(x, y, width, height, 0, 255, true);
}

void surfacerender::draw_outline(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, color color) 
{
	g_VGuiSurface->set_drawing_color(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
	g_VGuiSurface->draw_outlined_rect(x, y, width, height);
}

void surfacerender::draw_textured_polygon(std::int32_t vertices_count, Vertex_t* vertices, color color)
{
	static unsigned char buf[4] = { 255, 255, 255, 255 };

	unsigned int texture_id{};

	if (!texture_id)
	{
		texture_id = g_VGuiSurface->create_new_texture_id(true);
		g_VGuiSurface->set_texture_rgba(texture_id, buf, 1, 1);
	}

	g_VGuiSurface->set_drawing_color(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
	g_VGuiSurface->set_texture(texture_id);
	g_VGuiSurface->draw_polygon(vertices_count, vertices);
}

void surfacerender::draw_circle(std::int32_t x, std::int32_t y, std::int32_t radius, std::int32_t segments, color color)
{
	float step = M_PI * 2.0 / segments;

	for (float a = 0; a < (M_PI * 2.0); a += step) 
	{
		float x1 = radius * cos(a) + x;
		float y1 = radius * sin(a) + y;
		float x2 = radius * cos(a + step) + x;
		float y2 = radius * sin(a + step) + y;
		g_VGuiSurface->set_drawing_color(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
		g_VGuiSurface->draw_line(x1, y1, x2, y2);
	}
}

void surfacerender::draw_circle_filled(std::int32_t x, std::int32_t y, std::int32_t points, std::int32_t radius, color color) 
{
	std::vector<Vertex_t> vertices;
	float step = M_PI_F * 2.0f / points;
	for (float a = 0; a < (M_PI_F * 2.0f); a += step)
		vertices.push_back(Vertex_t(Vector2D(radius * cosf(a) + x, radius * sinf(a) + y)));

	g_VGuiSurface->set_drawing_color(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
	g_VGuiSurface->draw_textured_polygon(points, vertices.data());
}

void surfacerender::draw_corner_box(int x, int y, int w, int h, color color)
{
	g_VGuiSurface->set_drawing_color(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
	g_VGuiSurface->draw_line(x, y, x, y + (h / 5));
	g_VGuiSurface->draw_line(x, y, x + (w / 5), y);
	g_VGuiSurface->draw_line(x + w, y, x + w - (w / 5), y);
	g_VGuiSurface->draw_line(x + w, y, x + w, y + (h / 5));
	g_VGuiSurface->draw_line(x, y + h, x + (w / 5), y + h);
	g_VGuiSurface->draw_line(x, y + h, x, y + h - (h / 5));
	g_VGuiSurface->draw_line(x + w, y + h, x + w - (w / 5), y + h);
	g_VGuiSurface->draw_line(x + w, y + h, x + w, y + h - (h / 5));
}

Vector2D surfacerender::get_text_size(unsigned long font, std::string text)
{
	std::wstring a(text.begin(), text.end());

	const wchar_t* wstr = a.c_str();

	static int w, h;

	g_VGuiSurface->get_text_size(font, wstr, w, h);

	return { static_cast<float>(w), static_cast<float>(h) };
}