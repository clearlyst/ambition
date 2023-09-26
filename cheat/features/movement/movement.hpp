#pragma once

#include "../../menu.hpp"
#include "../../variables.hpp"
#include "../../helpers/xor.hpp"
#include "../../valve_sdk/sdk.hpp"
#include "../../helpers/singleton.hpp"
#include "../../valve_sdk/csgostructs.hpp"
#include "../engine prediction/prediction.hpp"

class movement : public singleton<movement>
{
public:
	void bunnyhop(CUserCmd* cmd);

    void resetdetection();

    void edgejump(CUserCmd* cmd);

	void minijump(CUserCmd* cmd);

	void longjump(CUserCmd* cmd);

    void ladderedgejump(CUserCmd* cmd);

	void jumpbug(CUserCmd* cmd);

	void autoduck(CUserCmd* cmd);

	void infinityduck(CUserCmd* cmd);

    void pre_prediction(CUserCmd* cmd);

    void autoedgebug(CUserCmd* cmd);

    void autoedgebug_lock(float& x, float& y);

    void autoalign(CUserCmd* cmd);

    void autopixelsurf(CUserCmd* cmd);

    void staminahop(CUserCmd* cmd);

    void mousespeedlimiter(float& x, float& y);

    void blockbot(CUserCmd* cmd);

    bool edgebug_should;
    bool pixelsurf_should;

    Vector edgebug_old_viewangles;

    int detecttick;
    int edgebugtick;

    bool ljsuccesful = 0;
    bool ejsuccesful = 0;
    bool jbsuccesful = 0;
    bool mjsuccesful = 0;
    bool agsuccesful = 0;
    bool pssuccesful = 0;
private:
    bool should_duck_next;
    bool do_strafe;
    bool do_duck;
    
    int edgebug_tick;
    int edgebug_prediction_ticks = 0;
    int edgebug_prediction_timestamp = 0;
    int edgebug_mouse_offset = 0;
    int edgebug_amount = 0;
};