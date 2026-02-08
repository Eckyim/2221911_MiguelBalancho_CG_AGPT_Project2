#include "pch.h"
#include "Box2DWorld.h"

#include <iostream>

Box2DWorld::Box2DWorld()
{
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = { 0.0f, 0.0f };
    worldId = b2CreateWorld(&worldDef);
}

Box2DWorld::~Box2DWorld()
{
    b2DestroyWorld(worldId);
}

void Box2DWorld::FixedUpdate(float deltaTime)
{
    b2World_Step(worldId, deltaTime, 4);


    std::vector<OverlapPair> overlaps = GetOverlaps();
    for (const OverlapPair& pair : overlaps)
    {
        pair.entityA->OnBeginOverlap(pair.entityB);
    }
}

std::vector<OverlapPair> Box2DWorld::GetOverlaps()
{
    std::vector<OverlapPair> overlaps;

    b2SensorEvents sensorEvents = b2World_GetSensorEvents(worldId);

    //if (sensorEvents.beginCount > 0) {
    //    std::cout << "Detected " << sensorEvents.beginCount << " sensor overlaps!" << std::endl;
    //}


    for (int i = 0; i < sensorEvents.beginCount; i++)
    {
        b2SensorBeginTouchEvent* event = sensorEvents.beginEvents + i;

        b2BodyId visitorBodyId = b2Shape_GetBody(event->visitorShapeId);
        b2BodyId sensorBodyId = b2Shape_GetBody(event->sensorShapeId);

        void* visitorData = b2Body_GetUserData(visitorBodyId);
        void* sensorData = b2Body_GetUserData(sensorBodyId);

        if (visitorData != nullptr && sensorData != nullptr)
        {
            Entity* entityA = static_cast<Entity*>(visitorData);
            Entity* entityB = static_cast<Entity*>(sensorData);

            overlaps.push_back({ entityA, entityB });
        }
    }

    return overlaps;
}