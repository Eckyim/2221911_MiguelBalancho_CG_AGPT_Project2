#include "Rock.h"
#include <iostream>

Rock::Rock(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height, bool metal, int size)
	:Enemy(engine, sheet, x, y, width, height)
{
	maxHP = 10 * size;
	currentHP = maxHP;

	moveSpeed = 150 / size;

	isMetal = metal;

	if (isMetal)
	{
		maxHP = 99999999;
		currentHP = maxHP;
	}

	rockSize = size;

	score = 10000 * size;

	contactDamage = 10 * size;

	CreatePhysicsBody();
	PlayAnimation("spin");
}

void Rock::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (direction == 0)
	{
		Move(-moveSpeed, 0, delta);
	}
	else if (direction == 1)
	{
		Move(-moveSpeed, (-moveSpeed/2), delta);
	}
	else if (direction == 2)
	{
		Move(-moveSpeed, (moveSpeed/2), delta);
	}
}

void Rock::TakeDamage(int damage)
{
	Enemy::TakeDamage(damage);

	if (currentHP <= 0)
	{
		engineRef->PlaySound("rocks");
	}
}

void Rock::OnDestroy()
{
	if (rockSize >= 3)
	{
		int y = GetY();
		
		nextSheet = engineRef->GetSpriteSheet("mediumRock");
		Rock* newRock1 = new Rock(engineRef, nextSheet, (GetX() + 64), (y - 64), 64, 64, false, 2);
		newRock1->SetDirection(1);
		Rock* newRock2 = new Rock(engineRef, nextSheet, GetX(), y, 64, 64, false, 2);
		Rock* newRock3 = new Rock(engineRef, nextSheet, (GetX() + 64), (y + 64), 64, 64, false, 2);
		newRock3->SetDirection(2);
	}
	else if (rockSize == 2)
	{
		int y = GetY();

		nextSheet = engineRef->GetSpriteSheet("smallRock");
		Rock* newRock1 = new Rock(engineRef, nextSheet, (GetX() + 32), (y - 32), 32, 32, false, 1);
		newRock1->SetDirection(1);
		Rock* newRock2 = new Rock(engineRef, nextSheet, GetX(), y, 32, 32, false, 1);
		Rock* newRock3 = new Rock(engineRef, nextSheet, (GetX() + 32), (y + 32), 32, 32, false, 1);
		newRock3->SetDirection(2);
	}
}

void Rock::SetDirection(int dir)
{
	direction = dir;
}
