#pragma once

#include "../../menu.hpp"
#include "../../variables.hpp"
#include "../../helpers/xor.hpp"
#include "../../helpers/math.hpp"
#include "../../valve_sdk/sdk.hpp"
#include "../movement/movement.hpp"
#include "../../helpers/singleton.hpp"
#include "../../renders/render-imgui.hpp"
#include "../../valve_sdk/csgostructs.hpp"
#include "../../valve_sdk/misc/Color.hpp"

class indicators : public singleton<indicators>
{
public:
	void velocity();

	void stamina();

	void velocitygraph_gather_data();

	void velograph_draw();

	void staminagraph_gather_data();

	void staminagraph_draw();

	void addindicators();
private:
	void add(std::string name, bool enabled, color clr);

	color lerp(color a, color b, float t);
	color huesaturationbrightnessalpha(float hue, float saturation, float brightness, float alpha);

	bool didjumplast = false;
	int last_delta_velocity = 0;
	int last_delta_stamina = 0;
	int last_velocity = 0;
	int pre_velocity = 0;
	int lasttick = 0;

	struct velocity_data_t
	{
		int speed;
		bool on_ground;
	};

	struct stamina_data_t
	{
		float stamina;
		bool on_ground;
	};

	int saved_tick_ej = 0;
	int saved_tick_lj = 0;
	int saved_tick_jb = 0;
	int saved_tick_eb = 0;
	int saved_tick_mj = 0;
	int saved_tick_ag = 0;
	int saved_tick_ps = 0;

	struct Indicator
	{
		color clr;
		float alpha;
	};

	std::unordered_map<std::string, Indicator> m_indicators;
	std::vector<velocity_data_t> velo_data;
	std::vector<stamina_data_t> stamina_data;
};