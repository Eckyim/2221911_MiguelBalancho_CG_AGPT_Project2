#pragma once

#include "CG_GameEngine.h"

class Missile : public Entity
{
private:
	int Damage;

	bool fromPlayer;

	SpriteSheet* explosion;

public:
	Missile(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height, int power);
	Missile(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height);


	void Update(float deltaTime) override;
	void OnBeginOverlap(Entity* other) override;

	void Explode();
};

