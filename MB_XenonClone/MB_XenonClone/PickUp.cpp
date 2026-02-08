#include "PickUp.h"


PickUp::PickUp(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height)
	:Entity(engine, sheet, x, y, width, height)
{
	dieHeight = -100;
	moveSpeed = 300.0f;


	CreatePhysicsBody();
	PlayAnimation("spin");
}

void PickUp::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	Move(-moveSpeed, 0, deltaTime);
	CheckHeight();
}

void PickUp::OnBeginOverlap(Entity* other)
{
	Player* player = dynamic_cast<Player*>(other);
	if (player)
	{
		engineRef->PlaySound("pickUp");
		ApplyPU(player);
		Destroy();
	}

	Companion* comp = dynamic_cast<Companion*>(other);
	if (comp)
	{
		engineRef->PlaySound("pickUp");
		ApplyPUComp(comp);
		Destroy();
	}


}

void PickUp::CheckHeight()
{
	if (GetX() <= dieHeight)
	{
		Destroy();
	}
}

void PickUp::ApplyPU(Player* player)
{
}

void PickUp::ApplyPUComp(Companion* comp)
{
}
