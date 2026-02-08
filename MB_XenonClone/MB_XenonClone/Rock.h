#pragma once

#include "CG_GameEngine.h"
#include "Enemy.h"

class Rock : public Enemy
{
private:

	int rockSize;
	bool isMetal;
	int direction = 0;

	SpriteSheet* nextSheet = nullptr;


public:
	Rock(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height, bool metal, int size);

	void Update(float deltaTime) override;

	void TakeDamage(int damage) override;

	void OnDestroy() override;
	void SetDirection(int dir);
};

