#include "CompanionPU.h"
#include "Companion.h"

void CompanionPU::ApplyPU(Player* player)
{
	Companion* comp = new Companion(engineRef, currentSheet, 0, 0, GetWidth(), GetHeight(), player);
	player->SetCompanion(comp);
}

void CompanionPU::ApplyPUComp(Companion* conmp)
{
	Player* playerRef = conmp->GetPlayerRef();
	Companion* companion = new Companion(engineRef, currentSheet, 0, 0, GetWidth(), GetHeight(), playerRef);
	playerRef->SetCompanion(companion);
}
