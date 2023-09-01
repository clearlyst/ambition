#pragma once

#include "../../menu.hpp"
#include "../../variables.hpp"
#include "../../helpers/xor.hpp"
#include "../backtrack/backtrack.hpp"
#include "../../helpers/singleton.hpp"
#include "../../valve_sdk/csgostructs.hpp"
#include "../../valve_sdk/misc/Color.hpp"

class aimbot : public singleton<aimbot>
{
public:
	void run(CUserCmd* cmd);

	variables::config::aimbot::aimbot_value_t get_current_settings();
private:

};