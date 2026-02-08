#include "Rusher.h"

Rusher::Rusher(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height)
	:Enemy(engine, sheet, x, y, width, height)
{
	maxHP = 15;
	currentHP = maxHP;

	moveSpeed = 250;

	contactDamage = 20;

	score = 5000;
	
	CreatePhysicsBody();

	PlayAnimation("idle");
}

void Rusher::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	Move(-moveSpeed, 0, deltaTime);
}

