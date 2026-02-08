#include "Spawner.h"

Spawner::Spawner(MyGameEngine* engine)
	:Object(engine)
{
	lonerSheet = engine->GetSpriteSheet("loner");
	rusherSheet = engine->GetSpriteSheet("rusher");
	droneSheet = engine->GetSpriteSheet("drone");
	
	rockSheet = engine->GetSpriteSheet("bigRock");
	rockMSheet = engine->GetSpriteSheet("bigMRock");

	comp1Sheet = engine->GetSpriteSheet("companionClone");
	comp2Sheet = engine->GetSpriteSheet("companionWingtip");

	spawnCD = 5;
	compSpawnCD = 20;
	droneSwarmSize = 8;
	droneCD = 0.2;
}

void Spawner::Update(float deltaTime)
{
	if (spawningDrones)
	{
		SpawningDrones(deltaTime);
	}

	if (canSpawnComp)
	{
		canSpawnComp = false;
		SpawnComp();
	}
	else
	{

		currentCompCD += deltaTime;

		if (currentCompCD >= compSpawnCD)
		{
			canSpawnComp = true;
			currentCompCD = 0;
		}
	}

	if (canSpawn)
	{
		canSpawn = false;
		int enemyType = rand() % 4;

		if (enemyType == 1)
		{
			SpawnLoner();
		}
		else if (enemyType == 2)
		{
			SpawnRusher();
		}
		else  if (enemyType == 3)
		{
			SpawnRock();
		}
		else
		{
			StartDrones();
		}
	}
	else
	{
		currentCD += deltaTime;

		if (currentCD >= spawnCD)
		{
			canSpawn = true;
			currentCD = 0;
		}
	}
}

void Spawner::SpawnLoner()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribX(300, 550);

	if (distribX(gen) % 2)
	{
		Loner* testloner = new Loner(engineRef, lonerSheet, distribX(gen), -100, 64, 64);
	}
	else
	{
		Loner* testloner = new Loner(engineRef, lonerSheet, distribX(gen), 550, 64, 64);
	}
}

void Spawner::SpawnRusher()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribY(130, 320);

	float y = distribY(gen);

	Rusher* testrusher = new Rusher(engineRef, rusherSheet, 650, y, 64, 32);
	Rusher* testrusher2 = new Rusher(engineRef, rusherSheet, 700, (y - 100), 64, 32);
	Rusher* testrusher3 = new Rusher(engineRef, rusherSheet, 750, (y + 100), 64, 32);
}

void Spawner::SpawnRock()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribY(200, 300);

	float y = distribY(gen);

	Rock* rock1 = new Rock(engineRef, rockSheet, 650, y, 96, 96, false, 3);
	Rock* rock2 = new Rock(engineRef, rockMSheet, 800, (y - 150), 96, 96, true, 3);
	Rock* rock3 = new Rock(engineRef, rockSheet, 950, (y + 150), 96, 96, false, 3);
}

void Spawner::StartDrones()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribY(130, 320);

	currentDroneY = distribY(gen);

	spawningDrones = true;
}

void Spawner::SpawningDrones(float deltaTime)
{
	if (currentdroneCD >= droneCD)
	{
		Drone* drone = new Drone(engineRef, droneSheet, 650, currentDroneY, 32, 32);
		currentdroneCD = 0;
		droneSpawned++;

		if (droneSpawned >= droneSwarmSize)
		{
			spawningDrones = false;
			droneSpawned = 0;
		}
	}
	else
	{
		currentdroneCD += deltaTime;
	}
}

void Spawner::SpawnComp()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribY(130, 320);

	if (rand()%2)
	{
		CompanionPU* comp = new CompanionPU(engineRef, comp1Sheet, 650, distribY(gen), 32, 32);
	}
	else
	{
		CompanionPU* comp = new CompanionPU(engineRef, comp2Sheet, 650, distribY(gen), 32, 64);
	}
}
