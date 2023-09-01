#pragma once

#include "../../helpers/xor.hpp"
#include "../../valve_sdk/sdk.hpp"
#include "../../helpers/singleton.hpp"
#include "../../valve_sdk/csgostructs.hpp"

#define TICK_INTERVAL            ( g_GlobalVars->interval_per_tick )
#define TIME_TO_TICKS( t )        ( (int)( 0.5f + (float)( t ) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )        ( TICK_INTERVAL * (float)( t ) )
#define ROUND_TO_TICKS( t )        ( TICK_INTERVAL * time_to_ticks( t ) )

class engine_prediction : public singleton<engine_prediction>
{
	friend class singleton<engine_prediction>;

	using md5_pseudo_random_fn = uint32_t(__thiscall*)(uint32_t);

	struct prediction_data
	{
		float curtime = 0.0f;
		float frametime = 0.0f;
		int m_fFlags;
		int m_nMoveType;
		Vector m_vecVelocity;
		Vector m_vecOrigin;
		bool in_prediction = false;
		bool first_time_predicted = false;
		md5_pseudo_random_fn md5_pseudo_random;
		uint32_t* prediction_random_seed;
		player_t** prediction_player;
		CMoveData move_data;
	};
public:
	void init();
	void repredict(CUserCmd* cmd);
	void restore();
	void updatepacket();

	prediction_data data;
	bool bInPrediction;
private:

};
