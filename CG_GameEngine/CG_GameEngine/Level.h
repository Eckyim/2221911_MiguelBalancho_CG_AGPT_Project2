#pragma once

class MyGameEngine;

class Level
{
protected:

	MyGameEngine* engineRef = nullptr;

public:

	Level(MyGameEngine* engine);
	virtual ~Level();
	
	void SetBackground(std::string path); 

	virtual void OnStart();
	virtual void OnUpdate(float deltaTime);
};

