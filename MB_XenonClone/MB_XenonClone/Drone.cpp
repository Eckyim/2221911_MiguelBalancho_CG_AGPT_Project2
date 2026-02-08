#include "Drone.h"

Drone::Drone(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height)
	:Enemy(engine, sheet, x, y, width, height)
{
	maxHP = 10;
	currentHP = maxHP;

	maxUp = y - 16;
	maxDown = y + 16;

	moveSpeed = 150;
	verticalSpeed = 75;

	contactDamage = 5;

	score = 1000;

	CreatePhysicsBody();

	PlayAnimation("idle");
}

void Drone::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	CheckHeight();

	MovementLoop();
}

void Drone::MovementLoop()
{

	if (GetY() >= maxDown)
	{
		goingDown = false;
	}

	if (GetY() <= maxUp)
	{
		goingDown = true;
	}

	if (goingDown)
	{
		Move(-moveSpeed, verticalSpeed, delta);
	}
	else
	{
		Move(-moveSpeed, -verticalSpeed, delta);
	}
}
