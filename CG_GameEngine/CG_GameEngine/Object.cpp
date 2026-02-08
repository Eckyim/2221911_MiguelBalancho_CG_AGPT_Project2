#include "pch.h"

#include <SDL3/SDL.h>
#include <iostream>

#include "CG_GameEngine.h"
#include "RenderingClass.h"
#include "Object.h"
#include "Texture.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "Rect.h"

Object::Object(MyGameEngine* engine)
{
    renderer = nullptr;

    engineRef = engine;
    engineRef->AddObject(this);

    objRect = new Rect(0, 0, 0, 0);
    currentSprite = nullptr;
    currentSheet = nullptr;
    currentAnimation = nullptr;
}

Object::Object(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height)
{
    renderer = nullptr;
    currentSprite = nullptr;
    currentAnimation = nullptr;
    currentSheet = sheet;
    objRect = new Rect(x, y, width, height);

    engineRef = engine;
    engineRef->AddObject(this);

    SetAnimations();
}

Object::Object(MyGameEngine* engine, Sprite* sprite, float x, float y, float width, float height)
{
    renderer = nullptr;
    currentAnimation = nullptr;
    currentSheet = nullptr;
    currentSprite = sprite;
    objRect = new Rect(x, y, width, height);

    engineRef = engine;
    engineRef->AddObject(this);
}

Object::Object(Sprite* sprite, float x, float y, float width, float height)
{
    engineRef = nullptr;
    renderer = nullptr;
    currentAnimation = nullptr;
    currentSheet = nullptr;
    currentSprite = sprite;
    objRect = new Rect(x, y, width, height);
}

Object::~Object()
{

    for (auto& pair : animations) {
        delete pair.second;
    }
    animations.clear();

    if (objRect != nullptr) {
        delete objRect;
        objRect = nullptr;
    }
}

void Object::SetAnimations()
{
    if (currentSheet != nullptr) 
    {
        for (auto& pair : currentSheet->GetAllAnimations()) {
            Animation* clonedAnim = pair.second->Clone();
            animations[pair.first] = clonedAnim;
        }
    }
}

void Object::SetRenderer(RenderingClass* rendering)
{
    if (rendering != nullptr) {
        renderer = rendering;
    }
}

void Object::Render()
{
    if (currentSprite == nullptr) return;
    renderer->DrawSprite(currentSprite, objRect);
}

void Object::Update(float deltaTime)
{
    delta = deltaTime;

    if (currentAnimation != nullptr) {
        currentAnimation->Update(deltaTime);
        currentSprite = currentAnimation->GetCurrentSprite();
    }
}

void Object::MoveObj(float deltaX, float deltaY, float deltaTime)
{
    float x = objRect->GetX() + deltaX * deltaTime;
    float y = objRect->GetY() + deltaY * deltaTime;


    objRect->SetPosition(x, y);
}

void Object::PlayAnimation(std::string name, bool restartIfSame)
{
    if (currentAnimation == nullptr) {
        PlayAnimation(name);
        return;
    }

    if (currentAnimation->GetName() == name)
    {
        if (restartIfSame)
        {
            PlayAnimation(name);
        }
    }
    else
    {
        PlayAnimation(name);
    }

}

void Object::PlayAnimation(std::string name)
{
    if (renderer == nullptr || currentSheet == nullptr) return;

    auto it = animations.find(name);
    if (it != animations.end()) {

        if (currentAnimation != nullptr) {
            currentAnimation->Stop();
        }

        currentAnimation = it->second;
        currentAnimation->Play();
    }
    else {
        std::cout << "Animation '" << name << "' not found!" << std::endl;
    }
}

void Object::StopAnimation()
{
    if (currentAnimation != nullptr) {
        currentAnimation->Stop();
    }
}

void Object::Destroy()
{
    OnDestroy();

    toBeDestroyed = true;
}

void Object::OnDestroy()
{
}

void Object::SetSprite(Sprite* sprite)
{
    currentSprite = sprite;
}

void Object::SetPosition(float x, float y)
{
    objRect->SetPosition(x, y);
}

void Object::SetSize(float width, float height)
{
    objRect->SetSize(width, height);
}

void Object::SetRotation(float radians)
{
    objRect->SetRotation(glm::radians(radians));
}

float Object::GetX()
{
    return objRect->GetX();
}

float Object::GetY()
{
    return objRect->GetY();
}

float Object::GetWidth()
{
    return objRect->GetW();
}

float Object::GetHeight()
{
    return objRect->GetH();
}

