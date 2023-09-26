#pragma once

#include "../../menu.hpp"
#include "../../variables.hpp"
#include "../../helpers/xor.hpp"
#include "../../valve_sdk/sdk.hpp"
#include "../../helpers/singleton.hpp"
#include "../../renders/render-imgui.hpp"
#include "../../valve_sdk/csgostructs.hpp"

class misc : public singleton<misc>
{
public:
	void spectatorlist();

	void watermark();

	void snipercrosshair();

	void spotifymusic();

	void changeviewmodeloffsets();

	void changeviewmodelfov();

	void changeweaponswayscale();

	void forcecrosshair();

	void recoilcrosshair();
	
	void rankreavel(CUserCmd* cmd);

	void usespammer(CUserCmd* cmd);

	void regionchanger();

	void removeflash();

	void removesmoke();

	void removefire();

private:
    std::string spotifytitle = "";

	float lasttime = 0.f;
};