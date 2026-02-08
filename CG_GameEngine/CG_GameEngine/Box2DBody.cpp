#include "pch.h"
#include "Box2DBody.h"

#include <iostream>

Box2DBody::Box2DBody()
{
    userData = nullptr;
    isValid = false;
}

Box2DBody::~Box2DBody()
{
    if (isValid) {
        b2DestroyBody(bodyId);
        isValid = false;
    }
}

void Box2DBody::Create(Entity* data, b2WorldId worldId, float xMeters, float yMeters,float widthMeters, float heightMeters)
{
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = { xMeters, yMeters };

    bodyId = b2CreateBody(worldId, &bodyDef);

    b2Polygon box = b2MakeBox(widthMeters / 2.0f, heightMeters / 2.0f);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.isSensor = true;
    shapeDef.enableSensorEvents = true;

    b2CreatePolygonShape(bodyId, &shapeDef, &box);

    isValid = true;

    userData = data;
    b2Body_SetUserData(bodyId, userData);

    //std::cout << "Created Box2D body at (" << xMeters << ", " << yMeters << ") size: " << widthMeters << "x" << heightMeters << std::endl;
}

void Box2DBody::SetPosition(float xMeters, float yMeters)
{
    if (!isValid) return;
    b2Body_SetTransform(bodyId, { xMeters, yMeters }, b2Rot_identity);
}

void Box2DBody::GetPosition(float& xMeters, float& yMeters)
{
    if (!isValid) return;
    b2Vec2 pos = b2Body_GetPosition(bodyId);
    xMeters = pos.x;
    yMeters = pos.y;
}


