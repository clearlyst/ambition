#include "notifications.hpp"

void notify::run(std::string text, bool console, bool chat, bool screen)
{
	if (console)
	{
		g_Console->console_color_printf({ variables::config::misc::screenmessage_color[0], variables::config::misc::screenmessage_color[1], variables::config::misc::screenmessage_color[2], 255 }, xorstr("weiamware"));
		g_Console->console_printf(xorstr(" | "));
		g_Console->console_printf(text.append(xorstr("\n")).c_str());
	}

	if (chat && g_ChatElements)
	{
		std::string randomcolor[16] = { xorstr("\x01"),  xorstr("\x02"), xorstr("\x03"),  xorstr("\x04"), xorstr("\x05"),  xorstr("\x06"),  xorstr("\x07"), xorstr("\x08"), xorstr("\x09"),  xorstr("\x10"),  xorstr("\x0A"),  xorstr("\x0B"),  xorstr("\x0C"),  xorstr("\x0D"), xorstr("\x0E"), xorstr("\x0F") };

		std::string picked_color;

		if (variables::config::misc::chatmessage_rainbow)
		{
			picked_color = (randomcolor[RandomInt(0, 15)]);
		}
		else
		{
			picked_color = (randomcolor[variables::config::misc::chatmessage_color]);
		}

		g_ChatElements->chat_printf(0, 0, std::string("").append(picked_color).append(xorstr("ambition")).append("\x01").append(xorstr(" | ")).append(text).c_str());
	}

	if (screen)
	{
		logs.push_front(loginfo_t(8.0f, text));
	}
}

void notify::draw()
{
	if (logs.empty())
	{
		return;
	}

	auto last_y = 5;


	for (unsigned int i = 0; i < logs.size(); i++)
	{
		auto& log = logs.at(i);

		log.log_time -= g_GlobalVars->frametime;

		if (log.log_time <= 0.f)
		{
			logs.erase(logs.begin() + i);
			continue;
		}

		float left = log.log_time;

		color m_color = color(255, 255, 255, 255);

		if (left < .5f) 
		{
			float factor = left;
			std::clamp(factor, 0.f, .5f);

			factor /= .5f;

			m_color.set_alpha((int)(factor * 255.f));

			if (i == 0 && factor < 0.2f)
			{
				log.y += 1 * (factor * 1.25);
			}
		}
		else
		{
			m_color.set_alpha(255);
		}

		imguirender::get().AddText(screenmessagefont, 10.0f, ImVec2(5, last_y - log.y), xorstr("ambition | ") + log.message, color(m_color), color(0, 0, 0), false, true);

		last_y += 15;
	}
}