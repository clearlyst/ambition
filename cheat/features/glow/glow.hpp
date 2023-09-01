#pragma once

#include "../../variables.hpp"
#include "../../helpers/xor.hpp"
#include "../../valve_sdk/sdk.hpp"
#include "../../helpers/singleton.hpp"
#include "../../valve_sdk/csgostructs.hpp"

class glow : public singleton<glow>
{
public:
	void run();
};