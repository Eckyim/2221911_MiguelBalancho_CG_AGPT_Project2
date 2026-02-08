#pragma once

#include "Object.h"

class Box2DBody;
class MyGameEngine;

class Entity : public Object
{
protected:
	float moveSpeed = 0;
	float ppm = 0;

	bool dying = false;

	Box2DBody* physicsBody = nullptr;
public:
	using Object::Object;
	virtual ~Entity();

	void Update(float deltaTime) override;

	void Move(float deltaX, float deltaY, float deltaTime);

	virtual void OnBeginOverlap(Entity* other) {}
	void SetPosition(float x, float y) override;

	void CreatePhysicsBody();
	void CreatePhysicsBody(float collisionWidth, float collisionHeight);
	void SetupPhysicsBody(float collisionWidth, float collisionHeight);
	void SyncPhysicsToSprite();
};

