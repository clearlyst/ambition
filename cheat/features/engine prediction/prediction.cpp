#include "prediction.hpp"

void engine_prediction::init()
{
	if (!data.prediction_player)
		data.prediction_player = *reinterpret_cast <player_t***>(Utils::PatternScan2("client.dll", "89 35 ? ? ? ? F3 0F 10 48") + 0x2);

	if (!data.prediction_random_seed)
		data.prediction_random_seed = *reinterpret_cast <uint32_t**>(Utils::PatternScan2("client.dll", "A3 ? ? ? ? 66 0F 6E 86") + 0x1);

	if (!data.md5_pseudo_random)
		data.md5_pseudo_random = reinterpret_cast<md5_pseudo_random_fn>(Utils::PatternScan2("client.dll", "55 8B EC 83 E4 F8 83 EC 70 6A"));

	data.in_prediction = g_Prediction->m_bInPrediction();
	data.first_time_predicted = g_Prediction->m_bIsFirstTimePredicted();

	data.m_fFlags = csgo::local_player->flags();
	data.m_vecVelocity = csgo::local_player->velocity();
	data.m_vecOrigin = csgo::local_player->abs_origin();
	data.m_nMoveType = csgo::local_player->move_type();

	data.curtime = g_GlobalVars->curtime;
	data.frametime = g_GlobalVars->frametime;

	updatepacket();

	g_Prediction->m_bInPrediction() = true;
	g_Prediction->m_bIsFirstTimePredicted() = false;
}

void engine_prediction::repredict(CUserCmd* cmd)
{
	// set current cmd
	*reinterpret_cast<CUserCmd**>(uint32_t(csgo::local_player) + 0x3348) = cmd;
	// set last cmd
	*reinterpret_cast<CUserCmd**>(uint32_t(csgo::local_player) + 0x3298) = cmd;

	*data.prediction_player = csgo::local_player;
	*data.prediction_random_seed = data.md5_pseudo_random(cmd->command_number) & 0x7FFFFFFF;

	bInPrediction = true;

	g_GlobalVars->curtime = TICKS_TO_TIME(csgo::local_player->get_tick_base());
	g_GlobalVars->frametime = g_Prediction->m_bEnginePaused() ? 0 : g_GlobalVars->interval_per_tick;

	cmd->buttons |= csgo::local_player->ButtonForced();
	cmd->buttons &= ~(csgo::local_player->ButtonDisabled());

	g_MoveHelper->SetHost(csgo::local_player);
	g_GameMovement->StartTrackPredictionErrors(csgo::local_player);

	const int iButtons = cmd->buttons;
	const int nButtonsChanged = iButtons ^ *reinterpret_cast<int*>(uintptr_t(csgo::local_player) + 0x3208);

	// m_afButtonLast
	*reinterpret_cast<int*>(uintptr_t(csgo::local_player) + 0x31FC) = (uintptr_t(csgo::local_player) + 0x3208);

	// m_nButtons
	*reinterpret_cast<int*>(uintptr_t(csgo::local_player) + 0x3208) = iButtons;

	// m_afButtonPressed
	*reinterpret_cast<int*>(uintptr_t(csgo::local_player) + 0x3200) = iButtons & nButtonsChanged;

	// m_afButtonReleased
	*reinterpret_cast<int*>(uintptr_t(csgo::local_player) + 0x3204) = nButtonsChanged & ~iButtons;


	if (csgo::local_player->PhysicsRunThink(0))
		csgo::local_player->PreThink();

	if (csgo::local_player->m_nNextThinkTick() != -1 && csgo::local_player->m_nNextThinkTick() > 0 && csgo::local_player->m_nNextThinkTick() <= csgo::local_player->get_tick_base())
	{
		csgo::local_player->m_nNextThinkTick() = -1;
		csgo::local_player->Think();
	}

	g_Prediction->SetupMove(csgo::local_player, cmd, g_MoveHelper, &data.move_data);
	g_GameMovement->SetupMovementBounds(&data.move_data);
	g_GameMovement->ProcessMovement(csgo::local_player, &data.move_data);

	g_Prediction->FinishMove(csgo::local_player, cmd, &data.move_data);

	g_MoveHelper->ProcessImpacts();

	csgo::local_player->PostThink();

	g_GameMovement->FinishTrackPredictionErrors(csgo::local_player);
	g_MoveHelper->SetHost(nullptr);
}

void engine_prediction::restore()
{
	*reinterpret_cast<CUserCmd**>(uint32_t(csgo::local_player) + 0x3348) = NULL;

	*data.prediction_player = nullptr;
	*data.prediction_random_seed = -1;

	g_GameMovement->Reset();

	g_GlobalVars->curtime = data.curtime;
	g_GlobalVars->frametime = data.frametime;

	g_Prediction->m_bInPrediction() = data.in_prediction;
	g_Prediction->m_bIsFirstTimePredicted() = data.first_time_predicted;

	bInPrediction = false;
}

void engine_prediction::updatepacket()
{
	if (!csgo::local_player)
		return;

	if (g_ClientState->m_nDeltaTick > 0)
	{
		g_Prediction->Update(
			g_ClientState->m_nDeltaTick,
			g_ClientState->m_nDeltaTick > 0,
			g_ClientState->m_nLastCommandAck,
			g_ClientState->m_nLastOutgoingCommand + g_ClientState->m_nChokedCommands
		);
	}
}