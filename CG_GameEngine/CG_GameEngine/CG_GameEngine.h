#pragma once

#include <string>
#include <vector>
#include <functional>

#include "Level.h"
#include "Object.h"
#include "Entity.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "TextSpriteSheet.h"
#include "Animation.h"
#include "Input.h" 
#include "UIClass.h"

class Window;
class RenderingClass;
class Event;
class Box2DWorld;
class Shader;
class AudioClass;

class MyGameEngine
{
public:
	MyGameEngine(std::string windowName, int screenwidth, int screenheight);
	~MyGameEngine();

	void SetLevel(Level* level);
	void SetBackground(std::string filePath);

	void EngineLoop();
	void render();
	void events();

	SpriteSheet* LoadSpriteSheet(std::string name, std::string filePath, int col, int row);
	SpriteSheet* GetSpriteSheet(std::string name);

	TextSpriteSheet* LoadFont(std::string name, std::string filePath, int col, int row);
	TextSpriteSheet* GetFont(std::string name);

	Object* CreateObject(Sprite* sprite, float x, float y, float width, float height);
	Object* CreateObject(SpriteSheet* sheet, float x, float y, float width, float height);
	void AddObject(Object* obj);
	void AddUI(UIClass* ui);

	void AddSound(std::string name, std::string filepath);
	void PlaySound(std::string name);

	void Stop() { isRunning = false; }

	Input* GetInput() { return input; }
	Box2DWorld* GetBox2DWorld() { return physicsWorld; }
	RenderingClass* GetRenderer() { return renderer; }
	std::vector<UIClass*> GetUIArray() { return UIArray; }
	AudioClass* GetAudioManager() { return audioManager; }

private:

	float deltaTime;
	int lastFrameTime;

	RenderingClass* renderer;
	Window* window;
	Event* event;
	Input* input;
	Level* currentLevel;
	AudioClass* audioManager;

	bool isRunning;
	Texture* bgImage;

	std::vector<Object*> objectArray;
	std::vector<UIClass*> UIArray;
	std::map<std::string, SpriteSheet*> spriteSheets;
	std::map<std::string, TextSpriteSheet*> fonts;

	Box2DWorld* physicsWorld;
};