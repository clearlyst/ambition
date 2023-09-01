#pragma once

#include <limits>
#include <time.h>

#include "../../menu.hpp"
#include "../../variables.hpp"
#include "../../helpers/xor.hpp"
#include "../../helpers/singleton.hpp"
#include "../../valve_sdk/csgostructs.hpp"
#include "../../valve_sdk/misc/Color.hpp"


class esp : public singleton<esp>
{
public:
	void run();
private:
	Vector pl_head;

	Vector pl_origin;

	bool visible;

	int alpha;

	RECT bbox;

	float player_alpha[65] = { };

	void box(player_t* target, color clr, color outline);
	
	void name(player_t* target, color clr);
	
	void bottom_bar(player_t* target, color clr);

	void flags(player_t* target, color clr);
	
	void healthbar(player_t* target, color clr, color outline);

	void skeleton(player_t* target, color clr);

	void outofview(player_t* target, color clr);

	void snapline(player_t* target, color clr);

	void viewangle(player_t* target, color clr);

	void head_box(player_t* player, color clr);
	
	void dlight(player_t* target, color clr);

	void throwed_grenade(entity_t* entity);

	void dropped_weapon(entity_t* entity);
};