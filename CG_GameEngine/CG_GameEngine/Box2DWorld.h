#pragma once
#include "Entity.h"
#include <box2d/box2d.h>  
#include <vector>


struct OverlapPair {
    Entity* entityA;
    Entity* entityB;
};

class Box2DWorld
{
private:
    b2WorldId worldId;

    const float pixelsPerMeter = 64.0f;

public:
    Box2DWorld();
    ~Box2DWorld();

    void FixedUpdate(float deltaTime);
    b2WorldId GetWorldId() { return worldId; }
    float GetPPM() { return pixelsPerMeter; }


    std::vector<OverlapPair> GetOverlaps();
};

