#pragma once

#include "CG_GameEngine.h"
#include "Player.h"
#include "Missile.h"

class Companion : public Entity
{
private:

	int maxHP;
	int currentHP;

	float xSpeed;
	float ySpeed;
	float xDif = 0;
	float yDif = 0;
	float xLimit;
	float yLimit;

	float baseX = 0;
	float baseY = 0;

	Player* playerRef = nullptr;
	bool isUp = false;

	int missilePower = 1;
	SpriteSheet* misileSheet = nullptr;

public:
	Companion(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height, Player* player);

	void Update(float deltaTime) override;

	void Movement();
	void TakeDamage(int damage);

	void SetUporDown(bool up);
	void AddPower();
	void Shoot();
	void Die();

	Player* GetPlayerRef() { return playerRef; }
};

