#pragma once

#include "helpers/xor.hpp"
#include "helpers/singleton.hpp"
#include "console debug/console.hpp"
#include "helpers/rpc/includes/discord_rpc.h"

class discordrpc : public singleton<discordrpc>
{
public:
	void initialize();
	void release();
};