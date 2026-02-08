#include "Enemy.h"
#include "Player.h"
#include "Companion.h"
#include "DamgePU.h"
#include "HealthPU.h"

#include <iostream>
#include "PickUp.h"

Enemy::Enemy(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height)
	:Entity(engine, sheet, x, y, width, height)
{
	maxHP = 20;
	currentHP = maxHP;
	contactDamage = 10;
	dieHeight = -150;
	score = 1;
	uiRef = nullptr;

	GetUI();
}

void Enemy::GetUI()
{
	for (UIClass* ui : engineRef->GetUIArray()) {
		InGameUI* gameUI = dynamic_cast<InGameUI*>(ui);
		if (gameUI)
		{
			uiRef = gameUI;
		}
	}
}

void Enemy::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	CheckHeight();
}

void Enemy::TakeDamage(int damage)
{
	currentHP -= damage;

	if (currentHP <= 0)
	{
		Destroy();
		if (uiRef != nullptr)
		{
			uiRef->AddScore(score);
			uiRef->ScorePopUp(score, GetX(), GetY());
		}


		if ((rand() % 10) == 1)
		{
			if (rand()%2)
			{
				SpriteSheet* powerUpSheet = engineRef->GetSpriteSheet("powerUpWeapon");
				DamgePU* powerUp = new DamgePU(engineRef, powerUpSheet, GetX(), GetY(), 32, 32);
			}
			else
			{
				SpriteSheet* powerUpSheet = engineRef->GetSpriteSheet("powerUpHP");
				HealthPU* powerUp = new HealthPU(engineRef, powerUpSheet, GetX(), GetY(), 32, 32);
			}
		}
	}
}

void Enemy::OnBeginOverlap(Entity* other)
{

	Player* player = dynamic_cast<Player*>(other);
	if (player)
	{
		player->TakeDamage(contactDamage);
	}

	Companion* comp = dynamic_cast<Companion*>(other);
	if (comp)
	{
		comp->TakeDamage(contactDamage);
	}
}

void Enemy::CheckHeight()
{
	if (GetX() <= dieHeight)
	{
		Destroy();
	}
}