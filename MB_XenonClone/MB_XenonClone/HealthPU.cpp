#include "HealthPU.h"


HealthPU::HealthPU(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height)
	:PickUp(engine, sheet, x, y, width, height)
{
	healAmmount = 50;
}

void HealthPU::ApplyPU(Player* player)
{
	player->TakeDamage(-healAmmount);
}

void HealthPU::ApplyPUComp(Companion* conmp)
{
	conmp->TakeDamage(-healAmmount);
}
