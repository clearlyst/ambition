#pragma once

#include "../../menu.hpp"
#include "../../variables.hpp"
#include "../../helpers/xor.hpp"
#include "../../helpers/singleton.hpp"
#include "../../valve_sdk/csgostructs.hpp"

class triggerbot : public singleton<triggerbot>
{
public:
	void run(CUserCmd* cmd);

	variables::config::triggerbot::triggerbot_value_t get_current_settings();
private:
};