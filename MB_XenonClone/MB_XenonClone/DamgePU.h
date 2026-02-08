#pragma once

#include "CG_GameEngine.h"
#include "PickUp.h"

class DamgePU : public PickUp
{
public:
	using PickUp::PickUp;

	void ApplyPU(Player* player) override;
	void ApplyPUComp(Companion* conmp) override;
};

