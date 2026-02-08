#include "DamgePU.h"

void DamgePU::ApplyPU(Player* player)
{
	player->damageUp();
}

void DamgePU::ApplyPUComp(Companion* conmp)
{
	conmp->AddPower();
}
