#include "Loner.h"
#include "Missile.h"

#include <iostream>

Loner::Loner(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height)
	:Enemy(engine, sheet, x, y, width, height)
{
	moveSpeed = 200;
	shootCD = 1.5f;
	contactDamage = 5;

	maxUp = 50;
	maxDown = 430;

	score = 10000;

	bulletSheet = engineRef->GetSpriteSheet("enBullet");

	CreatePhysicsBody();
	PlayAnimation("idle");
}

void Loner::Update(float deltaTime)
{
	Entity::Update(deltaTime);

	Shoot();
	MovementLoop();
}

void Loner::Shoot()
{
	if (canShoot)
	{
		float x = GetX();
		float y = GetY() + GetHeight() - 16;
		Missile* missile = new Missile(engineRef, bulletSheet, x, y, 16, 16);
		canShoot = false;


		engineRef->PlaySound("enShoot");
	}
	else
	{
		currentShootCD += delta;

		if (currentShootCD >= shootCD)
		{
			canShoot = true;
			currentShootCD = 0;
		}
	}
	
}

void Loner::MovementLoop()
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
		Move(0, moveSpeed, delta);
	}
	else
	{
		Move(0, -moveSpeed, delta);
	}
}

