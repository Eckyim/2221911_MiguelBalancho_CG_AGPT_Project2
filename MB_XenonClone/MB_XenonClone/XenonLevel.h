#pragma once

#include "CG_GameEngine.h"

class XenonLevel : public Level
{
private:


public:
	using Level::Level;

	void OnStart() override;
	void OnUpdate(float deltaTime) override;

	void CreateSprites();
	void CreateSounds();
};
