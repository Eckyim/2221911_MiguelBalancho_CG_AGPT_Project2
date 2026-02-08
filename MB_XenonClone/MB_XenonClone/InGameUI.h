#pragma once

#include "CG_GameEngine.h"
#include <iostream>
#include <fstream>

class InGameUI : public UIClass
{
private:

	int score = 0;
	int highScore = 0;
	TextRenderer* playerScore = nullptr;
	TextRenderer* highScoreText = nullptr;
	std::string highScoreFilePath;

	Object* hpBar = nullptr;
	Object* shieldBar = nullptr;
	std::vector<Object*> lifes;

	float scorePopUpLifeTime;
	int scoreNum = 0;
	std::map<std::string, float> scorePopUps;

public:
	using UIClass::UIClass;

	void SetUp() override;
	void OnUpdate(float deltaTime) override;
	void OnEnd() override;

	void SetHighScore();
	void AddScore(int scoreAdd);

	void ScorePopUp(int score, float x, float y);
	void UpdateScorePopUp(float deltaTime);

	void UpdateHealth(int currentHP);

	void SetLifes(int lifeAmmout);
	void RemoveLife();
};

