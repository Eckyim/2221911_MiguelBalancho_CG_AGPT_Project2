#pragma once

#include "CG_GameEngine.h"
#include "InGameUI.h"

class Enemy : public Entity
{
protected:

	int maxHP;
	int currentHP;
	int contactDamage;
	int dieHeight;
	int score;
	InGameUI* uiRef;
public:
	Enemy(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height);

	void GetUI();

	void Update(float deltaTime) override;

	virtual void TakeDamage(int damage);

	void OnBeginOverlap(Entity* other) override;

	void CheckHeight();
};
