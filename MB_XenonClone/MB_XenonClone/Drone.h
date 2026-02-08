#pragma once

#include "CG_GameEngine.h"
#include "Enemy.h"

class Drone : public Enemy
{
private:
	float verticalSpeed;
	int maxUp, maxDown;

	bool goingDown = true;
public:
	Drone(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height);

	void Update(float deltaTime) override;
	void MovementLoop();
};

