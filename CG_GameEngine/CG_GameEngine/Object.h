#pragma once

#include <string>
#include <map>
#include <vector>

class MyGameEngine;
class Sprite;
class SpriteSheet;
class Animation;
class Texture;
class RenderingClass;
class Rect;

class Object {
protected:
    MyGameEngine* engineRef;

    Sprite* currentSprite;
    SpriteSheet* currentSheet;
    Rect* objRect;
    RenderingClass* renderer;

    std::map<std::string, Animation*> animations;
    Animation* currentAnimation;

    float delta = 0;
    bool toBeDestroyed = false;

public:
    Object(MyGameEngine* engine);
    Object(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height);
    Object(MyGameEngine* engine, Sprite* sprite, float x, float y, float width, float height);
    Object(Sprite* sprite, float x, float y, float width, float height);

    virtual ~Object();


    void Render();
    virtual void Update(float deltaTime);

    void MoveObj(float deltaX, float deltaY, float deltaTime);

    void PlayAnimation(std::string name, bool restartIfSame);
    void PlayAnimation(std::string name);
    void StopAnimation();

    void Destroy();
    virtual void OnDestroy();

    void SetAnimations();
    void SetRenderer(RenderingClass* rendering);
    void SetSprite(Sprite* sprite);
    virtual void SetPosition(float x, float y);
    void SetSize(float width, float height);
    void SetRotation(float radians);

    bool GetToDestroy() { return toBeDestroyed; }
    float GetX();
    float GetY();
    float GetWidth();
    float GetHeight();
};