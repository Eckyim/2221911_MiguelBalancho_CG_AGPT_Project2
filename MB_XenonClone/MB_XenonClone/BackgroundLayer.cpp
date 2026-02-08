#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height)
    : Object(engine, sheet, x, y, width, height)
{
    scrollSpeed = 64;
    startX = 768;
    resetX = -128;

    rockSheet = sheet;

    Sprite* rockR1 = rockSheet->CreateCustomSprite(96, 1344, 160, 64);
    Sprite* rockR2 = rockSheet->CreateCustomSprite(64, 1408, 192, 64);
    Sprite* rockR3 = rockSheet->CreateCustomSprite(64, 1472, 192, 64);

    Sprite* rockL1 = rockSheet->CreateCustomSprite(288, 1344, 64, 64);
    Sprite* rockL2 = rockSheet->CreateCustomSprite(288, 1408, 64, 64);
    Sprite* rockL3 = rockSheet->CreateCustomSprite(288, 1472, 64, 64);

    Sprite* leftRocks[] = { rockL1, rockL2, rockL3 };
    Sprite* rightRocks[] = { rockR1, rockR2, rockR3 };

    for (int i = 0; i < 14; i++)
    {
        float x = 768 - (i * 64) + 64;
        Sprite* sprite = leftRocks[i % 3];
        Object* movingBlock = engineRef->CreateObject(sprite, x, 0, 64, 64);
        movingBlock->SetRotation(90);
        movingObjects.push_back(movingBlock);
    }

    for (int i = 0; i < 15; i++)
    {
        float x = 768 - (i * 64) + 64;
        Sprite* sprite = rightRocks[i % 3];
        Object* movingBlock = engineRef->CreateObject(sprite, x, 352, 192, 64);
        movingBlock->SetRotation(90);
        movingObjects.push_back(movingBlock);
    }

    
}

void BackgroundLayer::Update(float deltaTime)
{
    for (Object* obj : movingObjects)
    {
        if (obj->GetX() <= resetX)
        {
            obj->SetPosition(startX, obj->GetY());
        }
        else
        {
            obj->MoveObj(-scrollSpeed, 0, deltaTime);
        }
    }
}