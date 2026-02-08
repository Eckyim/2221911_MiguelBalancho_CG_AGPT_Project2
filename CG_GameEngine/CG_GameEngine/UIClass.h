#pragma once
#include "TextRenderer.h"
#include <string>

class MyGameEngine;

class UIClass
{
protected:
    MyGameEngine* engineRef;
    std::map<std::string, TextRenderer*> textRenders;
    std::map<std::string, Object*> sprites;

public:
    UIClass(MyGameEngine* engine);
    ~UIClass();

    void Render();

    TextRenderer* CreateText(std::string name, TextSpriteSheet* font, float x, float y, float cWidth, float cHeight);
    TextRenderer* GetText(std::string name);

    Object* CreateSprite(std::string name, Sprite* sprt, float x, float y, float w, float h);
    Object* GetSprite(std::string name);
    void RemoveSprite(std::string name);

    virtual void SetUp();
    virtual void OnUpdate(float deltaTime);
    virtual void OnEnd();
};