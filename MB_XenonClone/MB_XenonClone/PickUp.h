#pragma once

#include "CG_GameEngine.h"
#include "Player.h"
#include "Companion.h"

class PickUp : public Entity
{
private:
	int dieHeight;
public:
	PickUp(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height);

	void Update(float deltaTime) override;

	void OnBeginOverlap(Entity* other) override;

	void CheckHeight();
	virtual void ApplyPU(Player* player);
	virtual void ApplyPUComp(Companion* comp);

};

