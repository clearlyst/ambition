#pragma once

#include "../../variables.hpp"
#include "../../hooks/hooks.hpp"
#include "../../helpers/xor.hpp"
#include "../../valve_sdk/sdk.hpp"
#include "../../helpers/singleton.hpp"
#include "../../valve_sdk/csgostructs.hpp"
#include "../../valve_sdk/interfaces/IKeyValues.hpp"

class chams : public singleton<chams>
{
public:
	void initialize();
	void run(IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* matrix);
};