#pragma once
#include "CG_GameEngine.h"

class BackgroundLayer : public Object
{
private:
    float scrollSpeed;
    float resetX;
    float startX;

    SpriteSheet* rockSheet;
    std::vector<Object*> movingObjects;

public:
    BackgroundLayer(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height);

    void Update(float deltaTime) override;
};
