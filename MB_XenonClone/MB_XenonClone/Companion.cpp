#include "Companion.h"

#include <iostream>

Companion::Companion(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height, Player* player)
	:Entity(engine, sheet, x, y, width, height)
{
	playerRef = player;

	maxHP = 50;
	currentHP = maxHP;

	xSpeed = 5.0f;
	ySpeed = 1.0f;

	xLimit = 20.0f;
	yLimit = 10.0f;

	misileSheet = engineRef->GetSpriteSheet("missile");

	SetRotation(90);

	CreatePhysicsBody();

	PlayAnimation("spin");
}

void Companion::Update(float deltaTime)
{
	Entity::Update(deltaTime);

	Movement();
}

void Companion::Movement()
{
	if (dying) return;

	if (isUp)
	{
		baseX = playerRef->GetX() + (playerRef->GetWidth()/2) - (GetWidth()/2);
		baseY = playerRef->GetY() - playerRef->GetHeight();
	}
	else
	{
		baseX = playerRef->GetX() + (playerRef->GetWidth() / 2) - (GetWidth() / 2);
		baseY = playerRef->GetY() + (playerRef->GetHeight() * 1.5);
	}

	xDif += (xSpeed * delta);
	yDif += (ySpeed * delta);

	if (xDif >= xLimit || xDif <= -xLimit)
	{
		xSpeed *= -1;
	}

	if (yDif >= yLimit || yDif <= -yLimit)
	{
		ySpeed *= -1;
	}

	float x = baseX + xDif;
	float y = baseY + yDif;

	SetPosition(x, y);
}

void Companion::TakeDamage(int damage)
{
	currentHP -= damage;

	//std::cout << "HP: " << currentHP << std::endl;
	if (currentHP <= 0 && !dying)
	{
		Die();
	}
}

void Companion::SetUporDown(bool up)
{
	isUp = up;
}

void Companion::AddPower()
{
	missilePower++;
}

void Companion::Shoot()
{
	if (misileSheet == nullptr) return;

	float x = GetX() + GetWidth() - (GetWidth()/8);
	float y = GetY() + (GetHeight() / 2) - 8;
	Missile* missile = new Missile(engineRef, misileSheet, x, y, 16, 16, missilePower);
}

void Companion::Die()
{
	playerRef->RemoveCompanion(this);
	dying = true;
	PlayAnimation("die");
}
