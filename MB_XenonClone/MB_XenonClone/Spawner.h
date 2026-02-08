#pragma once
#include <random>

#include "CG_GameEngine.h"
#include "Loner.h"
#include "Rusher.h"
#include "Drone.h"
#include "Rock.h"
#include "CompanionPU.h"

class Spawner : public Object
{
private:

	float spawnCD;
	float currentCD = 0;
	bool canSpawn = false;

	float compSpawnCD;
	float currentCompCD = 0;
	bool canSpawnComp = false;

	float droneCD;
	float currentdroneCD = 0;
	int droneSpawned = 0;
	int droneSwarmSize = 0;
	bool spawningDrones = false;
	float currentDroneY = 0;

	std::random_device rd;

	SpriteSheet* lonerSheet;
	SpriteSheet* rusherSheet;
	SpriteSheet* droneSheet;
	SpriteSheet* rockSheet;
	SpriteSheet* rockMSheet;

	SpriteSheet* comp1Sheet;
	SpriteSheet* comp2Sheet;

public:
	Spawner(MyGameEngine* engine);

	void Update(float deltaTime) override;

	void SpawnLoner();
	void SpawnRusher();
	void SpawnRock();
	void StartDrones();
	void SpawningDrones(float deltaTime);
	void SpawnComp();
};

