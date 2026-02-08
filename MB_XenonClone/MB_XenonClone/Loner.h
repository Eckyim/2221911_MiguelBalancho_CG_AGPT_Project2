#pragma once

#include "CG_GameEngine.h"
#include "Enemy.h"

class Loner : public Enemy
{
private:

	float shootCD;

	int maxUp, maxDown;

	bool goingDown = true;
	bool canShoot = false;
	float currentShootCD = 0;
	SpriteSheet* bulletSheet = nullptr;

public:
	Loner(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height);

	void Update(float deltaTime) override;

	void Shoot();
	void MovementLoop();
};