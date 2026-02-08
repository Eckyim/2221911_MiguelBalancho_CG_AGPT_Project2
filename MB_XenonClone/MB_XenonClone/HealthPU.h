#pragma once

#include "CG_GameEngine.h"
#include "PickUp.h"

class HealthPU : public PickUp
{
private:
	int healAmmount;
public:
	HealthPU(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height);

	void ApplyPU(Player* player) override;
	void ApplyPUComp(Companion* conmp) override;
};

