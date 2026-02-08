#pragma once
#include <box2d/box2d.h>
#include "Entity.h"

class Box2DBody
{
private:
    b2BodyId bodyId;
    bool isValid;

    Entity* userData;
public:
    Box2DBody();
    ~Box2DBody();

    void Create(Entity* data, b2WorldId worldId, float xMeters, float yMeters,float widthMeters, float heightMeters);
    void SetPosition(float xMeters, float yMeters);
    void GetPosition(float& xMeters, float& yMeters);

    Entity* GetUserData() { return userData; }

    bool IsValid() { return isValid; }
    b2BodyId GetBodyId() { return bodyId; }
};