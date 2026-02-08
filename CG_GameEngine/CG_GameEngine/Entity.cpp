#include "pch.h"

#include <box2d/box2d.h> 

#include "CG_GameEngine.h" 
#include "Rect.h"
#include "Entity.h" 
#include "Box2DWorld.h" 
#include "Box2DBody.h" 

#include <iostream>

Entity::~Entity()
{
    if (physicsBody != nullptr) {
        delete physicsBody;
        physicsBody = nullptr;
    }
}

void Entity::Update(float deltaTime)
{
	Object::Update(deltaTime);

    if (dying)
    {
        if (!currentAnimation->IsPlaying())
        {
            Destroy();
        }
    }

}

void Entity::Move(float deltaX, float deltaY, float deltaTime)
{
    MoveObj(deltaX, deltaY, deltaTime);

    if (physicsBody != nullptr) {
        SyncPhysicsToSprite();
    }
}

void Entity::SetPosition(float x, float y)
{
    Object::SetPosition(x, y);

    if (physicsBody != nullptr) {
        SyncPhysicsToSprite();
    }
}

void Entity::CreatePhysicsBody()
{
    SetupPhysicsBody(GetWidth(), GetHeight());
}

void Entity::CreatePhysicsBody(float collisionWidth, float collisionHeight)
{
    SetupPhysicsBody(collisionWidth, collisionHeight);
}

void Entity::SetupPhysicsBody(float collisionWidth, float collisionHeight)
{

    if (engineRef == nullptr) {
        std::cout << "ERROR: engineRef is null!" << std::endl;
        return;
    }

    physicsBody = new Box2DBody();

    Box2DWorld* worldId = engineRef->GetBox2DWorld();
    ppm = worldId->GetPPM();

    float xMeters = (objRect->GetX() + objRect->GetW() / 2.0f) / ppm;
    float yMeters = (objRect->GetY() + objRect->GetH() / 2.0f) / ppm;
    float wMeters = collisionWidth / ppm;
    float hMeters = collisionHeight / ppm;

    physicsBody->Create(this, worldId->GetWorldId(), xMeters, yMeters, wMeters, hMeters);

    //std::cout << "Entity physics body created successfully" << std::endl;
}

void Entity::SyncPhysicsToSprite()
{
    if (physicsBody == nullptr || !physicsBody->IsValid()) return;

    float xMeters = (objRect->GetX() + objRect->GetW() / 2.0f) / ppm;
    float yMeters = (objRect->GetY() + objRect->GetH() / 2.0f) / ppm;

    physicsBody->SetPosition(xMeters, yMeters);
}