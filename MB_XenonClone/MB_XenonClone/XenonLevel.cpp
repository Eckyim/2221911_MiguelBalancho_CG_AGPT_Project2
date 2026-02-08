#include "XenonLevel.h"

#include "Player.h"
#include "Spawner.h"
#include "InGameUI.h"
#include "BackgroundLayer.h"


void XenonLevel::OnStart()
{
	CreateSprites();
	CreateSounds();
	SetBackground("resources/galaxy2.bmp");
	engineRef->PlaySound("music");

	BackgroundLayer* bgLayer = new BackgroundLayer(engineRef, engineRef->GetSpriteSheet("blocks"), 0, 0, 0, 0);

	Spawner* spawner = new Spawner(engineRef);
	InGameUI* UI = new InGameUI(engineRef);

	Object* boosters = engineRef->CreateObject(engineRef->GetSpriteSheet("booster")->GetSprite(0), 256, 400, 32, 32);

	Player* player = new Player(engineRef, engineRef->GetSpriteSheet("player"), 256, 400, 64, 64);
	player->SetBoosters(boosters);

}

void XenonLevel::OnUpdate(float deltaTime)
{
}

void XenonLevel::CreateSprites()
{
	SpriteSheet* playerSheet = engineRef->LoadSpriteSheet("player", "resources/ship2.bmp", 7, 3);
	playerSheet->CreateAnimation("idle", 3, 3, true, 5.0f);
	playerSheet->CreateAnimation("turnRight", 3, 6, false, 0.1f);
	playerSheet->CreateAnimation("righToCenter", 5, 4, false, 0.1f);
	playerSheet->CreateAnimation("turnLeft", 3, 0, false, 0.1f);
	playerSheet->CreateAnimation("leftToCenter", 1, 2, false, 0.1f);
	playerSheet->CreateAnimation("deathAnim", 14, 20, false, 0.1f);
	std::vector<int> blinkIndices = { 3, 10 };
	playerSheet->CreateAnimation("blink", blinkIndices, true, 0.1f);

	SpriteSheet* boosterSheet = engineRef->LoadSpriteSheet("booster", "resources/Burner1.bmp", 1, 1);

	SpriteSheet* misileSheet = engineRef->LoadSpriteSheet("missile", "resources/missile.bmp", 2, 3);
	misileSheet->CreateAnimation("level1", 0, 1, true, 0.1f);
	misileSheet->CreateAnimation("level2", 2, 3, true, 0.1f);
	misileSheet->CreateAnimation("level3", 4, 5, true, 0.1f);

	SpriteSheet* explosionSheet = engineRef->LoadSpriteSheet("explosion", "resources/explode16.bmp", 5, 2);
	explosionSheet->CreateAnimation("boom", 0, 9, false, 0.1f);

	SpriteSheet* lonerSheet = engineRef->LoadSpriteSheet("loner", "resources/LonerA.bmp", 4, 4);
	lonerSheet->CreateAnimation("idle", 0, 15, true, 0.1f);

	SpriteSheet* rusherSheet = engineRef->LoadSpriteSheet("rusher", "resources/rusher.bmp", 4, 6);
	rusherSheet->CreateAnimation("idle", 0, 23, true, 0.1f);

	SpriteSheet* droneSheet = engineRef->LoadSpriteSheet("drone", "resources/drone.bmp", 8, 2);
	droneSheet->CreateAnimation("idle", 0, 15, true, 0.1f);

	SpriteSheet* enBulletSheet = engineRef->LoadSpriteSheet("enBullet", "resources/EnWeap6.bmp", 8, 1);
	enBulletSheet->CreateAnimation("spin", 0, 7, true, 0.1f);

	SpriteSheet* bigRockSheet = engineRef->LoadSpriteSheet("bigRock", "resources/SAster96.bmp", 5, 5);
	bigRockSheet->CreateAnimation("spin", 0, 24, true, 0.1f);

	SpriteSheet* mediumRockSheet = engineRef->LoadSpriteSheet("mediumRock", "resources/SAster64.bmp", 8, 3);
	mediumRockSheet->CreateAnimation("spin", 0, 23, true, 0.1f);

	SpriteSheet* smallRockSheet = engineRef->LoadSpriteSheet("smallRock", "resources/SAster32.bmp", 8, 2);
	smallRockSheet->CreateAnimation("spin", 0, 15, true, 0.1f);

	SpriteSheet* bigMRockSheet = engineRef->LoadSpriteSheet("bigMRock", "resources/GAster96.bmp", 5, 5);
	bigMRockSheet->CreateAnimation("spin", 0, 24, true, 0.1f);

	SpriteSheet* mediumMRockSheet = engineRef->LoadSpriteSheet("mediumMRock", "resources/GAster64.bmp", 8, 3);
	mediumMRockSheet->CreateAnimation("spin", 0, 23, true, 0.1f);

	SpriteSheet* smallMRockSheet = engineRef->LoadSpriteSheet("smallMRock", "resources/GAster32.bmp", 8, 2);
	smallMRockSheet->CreateAnimation("spin", 0, 15, true, 0.1f);


	SpriteSheet* healthPUSheet = engineRef->LoadSpriteSheet("powerUpHP", "resources/PUShield.bmp", 4, 2);
	healthPUSheet->CreateAnimation("spin", 0, 7, true, 0.1f);

	SpriteSheet* damagePUSheet = engineRef->LoadSpriteSheet("powerUpWeapon", "resources/PUWeapon.bmp", 4, 2);
	damagePUSheet->CreateAnimation("spin", 0, 7, true, 0.1f);

	SpriteSheet* cloneSheet = engineRef->LoadSpriteSheet("companionClone", "resources/clone.bmp", 4, 5);
	cloneSheet->CreateAnimation("spin", 0, 15, true, 0.1f);
	cloneSheet->CreateAnimation("die", 16, 18, false, 0.1f);

	SpriteSheet* wingtipSheet = engineRef->LoadSpriteSheet("companionWingtip", "resources/wingtip.bmp", 4, 3);
	wingtipSheet->CreateAnimation("spin", 0, 7, true, 0.1f);
	wingtipSheet->CreateAnimation("die", 8, 10, false, 0.1f);

	SpriteSheet* blocksSheet = engineRef->LoadSpriteSheet("blocks", "resources/Blocks.bmp", 1, 1);

	SpriteSheet* shipIcon = engineRef->LoadSpriteSheet("shipIcon", "resources/PULife.bmp", 1, 1);
	SpriteSheet* helthColors = engineRef->LoadSpriteSheet("hpColors", "resources/HPCol.bmp", 2, 3);

	TextSpriteSheet* font8 = engineRef->LoadFont("font8", "resources/font8x8.bmp", 8, 16);
	TextSpriteSheet* font16 = engineRef->LoadFont("font16", "resources/font16x16.bmp", 8, 12);
}

void XenonLevel::CreateSounds()
{
	engineRef->AddSound("music", "resources/sounds/bg_music.wav");

	engineRef->AddSound("shoot", "resources/sounds/player_shoot.wav");
	engineRef->AddSound("warning", "resources/sounds/warning.wav");
	engineRef->AddSound("enShoot", "resources/sounds/enemy_shoot.wav");

	engineRef->AddSound("explosion", "resources/sounds/explosion.wav");
	engineRef->AddSound("pickUp", "resources/sounds/pick_up.wav");
	engineRef->AddSound("rocks", "resources/sounds/rocks.wav");
}
