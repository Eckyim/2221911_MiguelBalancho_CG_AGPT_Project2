#pragma once

#include "CG_GameEngine.h"
#include "Enemy.h"

class Rusher : public Enemy
{
public:
	Rusher(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height);

	void Update(float deltaTime) override;
};

