#include "Missile.h"
#include "Enemy.h"
#include "Player.h"
#include "Companion.h"
#include "Explosion.h"
#include <iostream>

Missile::Missile(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height, int power)
	:Entity(engine, sheet, x, y, width, height)
{
	moveSpeed = 600.0f;
	Damage = 5;
	fromPlayer = true;

	explosion = engineRef->GetSpriteSheet("explosion");

	SetRotation(90);
	CreatePhysicsBody();

	if (power == 1)
	{
		PlayAnimation("level1");
	}
	else if (power == 2)
	{
		PlayAnimation("level2");
		Damage = Damage * 2;
	}
	else if (power >= 3)
	{
		PlayAnimation("level3");
		Damage = Damage * 4;
	}
}

Missile::Missile(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height)
	:Entity(engine, sheet, x, y, width, height)
{
	moveSpeed = 200.0f;
	Damage = 10;
	fromPlayer = false;

	explosion = engineRef->GetSpriteSheet("explosion");

	SetRotation(90);
	CreatePhysicsBody(8, 8);
	PlayAnimation("spin");
}

void Missile::Update(float deltaTime)
{
	Entity::Update(deltaTime);


	if (fromPlayer)
	{
		Move(moveSpeed, 0, deltaTime);
	}
	else
	{
		Move(-moveSpeed, 0, deltaTime);
	}

	if (GetX() < -50 || GetX() > 700)
	{
		Destroy();
	}
}

void Missile::OnBeginOverlap(Entity* other)
{
	if (fromPlayer)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(other);
		if (enemy)
		{
			Explode();
			enemy->TakeDamage(Damage);
			Destroy();
		}
	}
	else
	{
		Player* player = dynamic_cast<Player*>(other);
		if (player)
		{
			Explode();
			player->TakeDamage(Damage);
			Destroy();
		}

		Companion* comp = dynamic_cast<Companion*>(other);
		if (comp)
		{
			Explode();
			comp->TakeDamage(Damage);
			Destroy();
		}
	}
}

void Missile::Explode()
{
	float x = GetX() + (GetWidth()/2) - 16;
	float y = GetY() - 16;
	Explosion* explode = new Explosion(engineRef, explosion, x, y, 16, 16);
}
