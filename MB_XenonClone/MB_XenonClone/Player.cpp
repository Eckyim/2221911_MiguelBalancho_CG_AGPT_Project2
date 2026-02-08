#include "Player.h"
#include "Missile.h"
#include "Companion.h"

#include <iostream>

Player::Player(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height)
	:Entity(engine, sheet, x, y, width, height)
{
	input = engineRef->GetInput();

	maxHP = 100;
	currentHP = maxHP;
	lifes = 3;
	invCD = 2.0f;

	moveSpeed = 300.0f;
	shootCD = 0.2f;

	misileSheet = engineRef->GetSpriteSheet("missile");
	GetUI();
	
	SetRotation(90);

	CreatePhysicsBody(32, 32);

	PlayAnimation("idle");

}

void Player::GetUI()
{
	for (UIClass* ui : engineRef->GetUIArray()) {
		InGameUI* gameUI = dynamic_cast<InGameUI*>(ui);
		if (gameUI)
		{
			uiRef = gameUI;
		}
	}
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime);

	CalcShootCD();
	CalcInvCD();

	UpdateBoosters();

	CheckInput();

	ManageAnimations();
}

void Player::CheckInput()
{
	if (input == nullptr) return;

	if (dying) return;

	xDir = 0;
	yDir = 0;

	if (input->GetKey(Key::W) || input->GetKey(Key::UP)) {
		yDir -= 1;
	}
	if (input->GetKey(Key::A) || input->GetKey(Key::LEFT)) {
		xDir -= 1;
	}
	if (input->GetKey(Key::S) || input->GetKey(Key::DOWN)) {
		yDir += 1;
	}
	if (input->GetKey(Key::D) || input->GetKey(Key::RIGHT)) {
		xDir += 1;
	}

	if (input->GetKey(Key::SPACE)) {
		Shoot();
	}


	if (input->IsControllerConnected()) 
	{
		float axisX = input->GetControllerAxis(GamepadAxis::LEFT_X);
		float axisY = input->GetControllerAxis(GamepadAxis::LEFT_Y);

		if (abs(axisX) > 0.15f) xDir = axisX;
		if (abs(axisY) > 0.15f) yDir = axisY;

		if (input->GetControllerButton(GamepadButton::XBOX_A)) {
			Shoot();
		}
	}

	if (xDir != 0 || yDir != 0)
	{
		if (GetX() <= 0 && xDir <= 0) xDir = 0;
		if (GetY() <= 0 && yDir <= 0) yDir = 0;
		if ((GetX() + GetWidth()) >= 640 && xDir >= 0) xDir = 0;
		if ((GetY() + GetHeight()) >= 480 && yDir >= 0) yDir = 0;

		Move(xDir * moveSpeed, yDir * moveSpeed, delta);
	}
}

void Player::ManageAnimations()
{
	if (currentAnimation == NULL) return;

	if (dying) 
	{
		PlayAnimation("deathAnim", false);
		return;
	} 

	if (invulnerable) PlayAnimation("blink", false);

	if (yDir != 0)
	{
		if (yDir > 0)
		{
			if (currentAnimation->GetName() == "idle")
			{
				PlayAnimation("turnRight", false);
			}

			if (currentAnimation->GetName() == "turnLeft")
			{
				PlayAnimation("leftToCenter", false);
			}

			if (currentAnimation->GetName() == "leftToCenter")
			{
				if (!currentAnimation->IsPlaying())
				{
					PlayAnimation("turnRight", false);
				}
			}
		}

		if (yDir < 0)
		{
			if (currentAnimation->GetName() == "idle")
			{
				PlayAnimation("turnLeft", false);
			}

			if (currentAnimation->GetName() == "turnRight")
			{
				PlayAnimation("righToCenter", false);
			}

			if (currentAnimation->GetName() == "righToCenter")
			{
				if (!currentAnimation->IsPlaying())
				{
					PlayAnimation("turnLeft", false);
				}
			}
		}
	}
	else
	{
		if (currentAnimation->GetName() == "turnLeft")
		{
			PlayAnimation("leftToCenter", false);
		}

		if (currentAnimation->GetName() == "leftToCenter")
		{
			if (!currentAnimation->IsPlaying())
			{
				PlayAnimation("idle", false);
			}
		}

		if (currentAnimation->GetName() == "turnRight")
		{
			PlayAnimation("righToCenter", false);
		}

		if (currentAnimation->GetName() == "righToCenter")
		{
			if (!currentAnimation->IsPlaying())
			{
				PlayAnimation("idle", false);
			}
		}


		if (currentAnimation->GetName() == "blink")
		{
			if (!invulnerable)
			{
				PlayAnimation("idle", false);
			}
		}
	}
}

void Player::TakeDamage(int damage)
{
	if (invulnerable) return;

	currentHP -= damage;

	if (currentHP <= 0)
	{
		lifes--;

		if (lifes > 0)
		{
			currentHP = maxHP;
			missilePower = 1;

			engineRef->PlaySound("warning");
			invulnerable = true;
		}

		if (companiomUp != nullptr)
		{
			companiomUp->Die();
		}

		if (companiomDown != nullptr)
		{
			companiomDown->Die();
		}

		if (uiRef != nullptr)
		{
			uiRef->RemoveLife();
		}

		if (lifes == 0)
		{
			dying = true;
		}

	}

	if (currentHP >= (maxHP * 2))
	{
		currentHP = maxHP * 2;
	}

	if (uiRef != nullptr)
	{
		uiRef->UpdateHealth(currentHP);
	}
}

void Player::damageUp()
{
	missilePower++;

	if (companiomUp != nullptr)
	{
		companiomUp->AddPower();
	}

	if (companiomDown != nullptr)
	{
		companiomDown->AddPower();
	}
}

void Player::CalcInvCD()
{
	if (invulnerable)
	{
		currentInvCD += delta;

		if (currentInvCD >= invCD)
		{
			invulnerable = false;
			currentInvCD = 0;
		}
	}
}

void Player::UpdateBoosters()
{
	if (!boosters) return;

	if (dying)
	{
		boosters->Destroy();
		boosters = nullptr;
		return;
	}

	float w = 32 + (-(rand() % 8) + (rand() % 8));
	float x = GetX() - (GetWidth() / 2) + 8 - w+32;
	float y = GetY() + 16;
	
	boosters->SetPosition(x, y);
	boosters->SetSize(w, boosters->GetHeight());
}

void Player::CalcShootCD()
{
	if (!canShoot)
	{
		currentShootCD += delta;

		if (currentShootCD >= shootCD)
		{
			canShoot = true;
			currentShootCD = 0;
		}
	}
}

void Player::Shoot()
{
	if (canShoot)
	{
		if (misileSheet == nullptr) return;

		engineRef->PlaySound("shoot");

		float x = GetX() + GetWidth() - 8;
		float y = GetY() + (GetHeight() / 2) - 8;
		Missile* missile = new Missile(engineRef, misileSheet, x, y, 16, 16, missilePower);
		canShoot = false;



		if (companiomUp != nullptr)
		{
			companiomUp->Shoot();
		}

		if (companiomDown != nullptr)
		{
			companiomDown->Shoot();
		}
	}
}

void Player::SetBoosters(Object* booster)
{
	boosters = booster;
	boosters->SetRotation(90);
}

void Player::SetCompanion(Companion* comp)
{
	if (companiomUp == nullptr)
	{
		companiomUp = comp;
		companiomUp->SetUporDown(true);
	}
	else if (companiomDown == nullptr)
	{
		companiomDown = comp;
		companiomDown->SetUporDown(false);
	}
	else
	{
		comp->Destroy();
		comp = nullptr;
	}
}

void Player::RemoveCompanion(Companion* comp)
{
	if (companiomUp == comp)
	{
		companiomUp = nullptr;
	}

	if (companiomDown == comp)
	{
		companiomDown = nullptr;
	}
}

void Player::OnDestroy()
{
	engineRef->Stop();
}
