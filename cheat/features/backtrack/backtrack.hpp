#pragma once

#include "../../menu.hpp"
#include "../../variables.hpp"
#include "../aimbot/aimbot.hpp"
#include "../../helpers/xor.hpp"
#include "../../helpers/singleton.hpp"
#include "../../valve_sdk/csgostructs.hpp"

struct backtrack_data 
{
	float sim_time;
	Vector hitbox_position;
	matrix3x4_t boneMatrix[128];
	matrix3x4_t boneMatrixCur[128];
};

class backtrack : public singleton<backtrack>
{
public:
	void run(CUserCmd* cmd);

	float latency = 0.0f;
	float lerp_time = 0.0f;
	float correct_time = 0.0f;
	float delta_time = 0.0f;

	std::map<int, std::deque<backtrack_data>> data;
private:
};