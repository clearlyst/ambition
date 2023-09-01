#pragma once
#include <deque>

#include "../../menu.hpp"
#include "../../variables.hpp"
#include "../../helpers/xor.hpp"
#include "../../valve_sdk/sdk.hpp"
#include "../../helpers/singleton.hpp"
#include "../../renders/render-imgui.hpp"
#include "../../valve_sdk/csgostructs.hpp"

class notify : public singleton<notify>
{
public:
	void run(std::string text, bool console, bool chat, bool screen);

	void draw();

private:
	struct loginfo_t 
	{
		loginfo_t(const float log_time, std::string message)
		{
			this->log_time = log_time;
			this->message = message;
		}

		float log_time;
		std::string message;
		float x, y;
	};

	std::deque< loginfo_t > logs;
};