#pragma once

#include "CG_GameEngine.h"
#include "InGameUI.h"

class Companion;

class Player : public Entity
{
private:

	Input* input;

	int maxHP;
	int currentHP;

	int lifes;
	bool invulnerable = false;
	float invCD;
	float currentInvCD = 0;

	float xDir = 0;
	float yDir = 0;

	float shootCD;
	int missilePower = 1;
	bool canShoot = true;
	float currentShootCD = 0;

	InGameUI* uiRef = nullptr;
	SpriteSheet* misileSheet = nullptr;
	Object* boosters = nullptr;
	Companion* companiomUp = nullptr;
	Companion* companiomDown = nullptr;

public:
	Player(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height);
	void GetUI();

	void Update(float deltaTime) override;
	void CheckInput();
	void ManageAnimations();

	void TakeDamage(int damage);
	void damageUp();

	void CalcInvCD();
	void UpdateBoosters();
	void CalcShootCD();
	void Shoot();
	void SetBoosters(Object* booster);
	void SetCompanion(Companion* comp);
	void RemoveCompanion(Companion* comp);

	void OnDestroy() override;
};

