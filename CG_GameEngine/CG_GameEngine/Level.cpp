#include "pch.h"
#include "CG_GameEngine.h"
#include "Level.h"

Level::Level(MyGameEngine* engine)
{
	engineRef = engine;
}

Level::~Level()
{
}

void Level::SetBackground(std::string path)
{
	engineRef->SetBackground(path);
}

void Level::OnStart()
{
}

void Level::OnUpdate(float deltaTime)
{
}
