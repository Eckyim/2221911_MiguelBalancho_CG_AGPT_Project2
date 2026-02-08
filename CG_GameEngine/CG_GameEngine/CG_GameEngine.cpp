#include "pch.h"
#include "framework.h"

#include <iostream>
#include <SDL3/SDL.h>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "CG_GameEngine.h" 
#include "Window.h"
#include "Event.h"
#include "Box2DWorld.h"
#include "Shader.h"
#include "Texture.h"
#include "RenderingClass.h"
#include "AudioClass.h"

MyGameEngine::MyGameEngine(std::string windowName, int screenwidth, int screenheight)
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_AUDIO)) {
		std::cout << "SDL Init Error" << std::endl;
		return;
	}

	isRunning = true;
	bgImage = nullptr;
	deltaTime = 0.0f;
	lastFrameTime = 0;
	currentLevel = nullptr;

	window = new Window(windowName, screenwidth, screenheight);
	renderer = new RenderingClass(window);
	event = new Event();
	input = new Input();
	physicsWorld = new Box2DWorld();
	audioManager = new AudioClass();

	std::cout << "Engine initialized with OpenGL" << std::endl;
}

MyGameEngine::~MyGameEngine()
{
	if (currentLevel != nullptr) {
		delete currentLevel;
		currentLevel = nullptr;
	}

	for (Object* obj : objectArray) {
		delete obj;
	}
	objectArray.clear();

	for (UIClass* ui : UIArray) {
		delete ui;
	}
	UIArray.clear();

	for (auto& pair : spriteSheets) {
		delete pair.second;
	}
	spriteSheets.clear();

	for (auto& pair : fonts) {
		delete pair.second;
	}
	fonts.clear();

	if (bgImage != nullptr) {
		delete bgImage;
		bgImage = nullptr;
	}

	if (renderer != nullptr) {
		delete renderer;
		renderer = nullptr;
	}

	if (window != nullptr) {
		delete window;
		window = nullptr;
	}

	if (input != nullptr) {
		delete input;
		input = nullptr;
	}

	if (physicsWorld != nullptr) {
		delete physicsWorld;
		physicsWorld = nullptr;
	}

	if (audioManager != nullptr) {
		delete audioManager;
		audioManager = nullptr;
	}

	SDL_Quit();
}

void MyGameEngine::SetLevel(Level* level)
{
	currentLevel = level;
}

void MyGameEngine::SetBackground(std::string filePath)
{
	if (bgImage != nullptr) {
		delete bgImage;
		bgImage = nullptr;
	}

	bgImage = new Texture(filePath);
}

void MyGameEngine::EngineLoop()
{
	if (!currentLevel) return;

	lastFrameTime = SDL_GetTicks();

	currentLevel->OnStart();
	for (UIClass* ui : UIArray) {
		ui->SetUp();
	}

	while (isRunning)
	{
		int now = SDL_GetTicks();
		deltaTime = (now - lastFrameTime) / 1000.0f;
		lastFrameTime = now;

		physicsWorld->FixedUpdate(deltaTime);

		events();

		currentLevel->OnUpdate(deltaTime);

		for (int i = objectArray.size() - 1; i >= 0; i--)
		{
			objectArray[i]->Update(deltaTime);

			if (objectArray[i]->GetToDestroy())
			{
				delete objectArray[i];
				objectArray.erase(objectArray.begin() + i);
			}
		}

		for (int i = UIArray.size() - 1; i >= 0; i--)
		{
			UIArray[i]->OnUpdate(deltaTime);
		}

		audioManager->Update();
		render();
	}


	for (int i = UIArray.size() - 1; i >= 0; i--)
	{
		UIArray[i]->OnEnd();
	}

}

void MyGameEngine::render()
{
	renderer->ClearFrame();

	if (bgImage != nullptr) {
		renderer->DrawTextureFullScreen(bgImage);
	}

	for(Object* objects : objectArray)
	{
		renderer->DrawObject(objects);
	}

	for (UIClass* ui : UIArray)
	{
		renderer->DrawUI(ui);
	}

	renderer->ShowFrame();
}

void MyGameEngine::events()
{
	while (SDL_PollEvent(event->GetSDLEvent()))
	{
		if (event->VerifyType(SDL_EVENT_QUIT))
			isRunning = false;

		if (event->VerifyType(SDL_EVENT_GAMEPAD_ADDED)) {
			input->OnControllerAdded(event->GetGamepadDeviceID());
		}

		if (event->VerifyType(SDL_EVENT_GAMEPAD_REMOVED)) {
			input->OnControllerRemoved(event->GetGamepadDeviceID());
		}

		if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_ESCAPE])
			isRunning = false;
	}
}

SpriteSheet* MyGameEngine::LoadSpriteSheet(std::string name, std::string filePath, int col, int row)
{
	auto it = spriteSheets.find(name);
	if (it != spriteSheets.end()) {
		std::cout << "SpriteSheet '" << name << "' already loaded." << std::endl;
		return it->second;
	}

	SpriteSheet* sheet = new SpriteSheet(filePath, col, row);
	spriteSheets[name] = sheet;
	
	return sheet;
}

SpriteSheet* MyGameEngine::GetSpriteSheet(std::string name)
{
	auto it = spriteSheets.find(name);
	if (it != spriteSheets.end()) {
		return it->second;
	}

	std::cout << "Error: SpriteSheet '" << name << "' not found!" << std::endl;
	return nullptr;
}

TextSpriteSheet* MyGameEngine::LoadFont(std::string name, std::string filePath, int col, int row)
{
	auto it = fonts.find(name);
	if (it != fonts.end()) {
		std::cout << "Font '" << name << "' already loaded." << std::endl;
		return it->second;
	}

	TextSpriteSheet* font = new TextSpriteSheet(filePath, col, row);
	fonts[name] = font;

	return font;
}

TextSpriteSheet* MyGameEngine::GetFont(std::string name)
{
	auto it = fonts.find(name);
	if (it != fonts.end()) {
		return it->second;
	}

	std::cout << "Error: Font '" << name << "' not found!" << std::endl;
	return nullptr;
}

Object* MyGameEngine::CreateObject(Sprite* sprite, float x, float y, float width, float height)
{
	if (renderer == nullptr) {
		std::cout << "Error: No Renderer on create object" << std::endl;
		return nullptr;
	}

	Object* newobject = new Object(this, sprite, x, y, width, height);
	return newobject;
}

Object* MyGameEngine::CreateObject(SpriteSheet* sheet, float x, float y, float width, float height)
{
	if (renderer == nullptr) {
		std::cout << "Error: No Renderer on create object" << std::endl;
		return nullptr;
	}

	Object* newobject = new Object(this, sheet, x, y, width, height);
	return newobject;
}

void MyGameEngine::AddObject(Object* obj)
{
	if (obj != nullptr) {
		obj->SetRenderer(renderer);
		objectArray.push_back(obj);
	}
}

void MyGameEngine::AddUI(UIClass* ui)
{
	if (ui != nullptr) {
		UIArray.push_back(ui);
	}
}

void MyGameEngine::AddSound(std::string name, std::string filepath)
{
	audioManager->LoadSound(name, filepath);
}

void MyGameEngine::PlaySound(std::string name)
{
	audioManager->PlaySound(name);
}
