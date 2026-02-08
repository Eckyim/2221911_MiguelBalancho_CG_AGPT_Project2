#include "InGameUI.h"


void InGameUI::SetUp()
{
	scorePopUpLifeTime = 1.0f;
	highScoreFilePath = "resources/txt/HighScore.txt";

	TextRenderer* highScoreLabel = CreateText("highScoreLabel", engineRef->GetFont("font8"), 320, 10, 8, 8);
	highScoreLabel->SetText("High Score");
	highScoreLabel->SetCentered(true);

	highScoreText = CreateText("highScore", engineRef->GetFont("font8"), 320, 20, 8, 8);
	highScoreText->SetCentered(true);
	SetHighScore();

	TextRenderer* playerLabel = CreateText("playerLabel", engineRef->GetFont("font8"), 10, 10, 8, 8);
	playerLabel->SetText("Player One");

	playerScore = CreateText("Score", engineRef->GetFont("font16"), 10, 20, 16, 16);
	playerScore->SetText("0000000000");



	CreateSprite("bg_hpBar", engineRef->GetSpriteSheet("hpColors")->GetSprite(4), 10, 450, 200, 20);

	hpBar = CreateSprite("hpBar", engineRef->GetSpriteSheet("hpColors")->GetSprite(0), 14, 454, 192, 12);

	shieldBar = CreateSprite("shieldBar", engineRef->GetSpriteSheet("hpColors")->GetSprite(3), 14, 454, 0, 12);
	
	SetLifes(3);
}

void InGameUI::OnUpdate(float deltaTime)
{
	UpdateScorePopUp(deltaTime);
}

void InGameUI::OnEnd()
{
	if (score >= highScore)
	{
		std::ofstream highScoreFile(highScoreFilePath);

		highScoreFile << std::to_string(score);

		highScoreFile.close();
	}
}

void InGameUI::SetHighScore()
{
	std::string myText;

	std::ifstream highScoreFile(highScoreFilePath);

	getline(highScoreFile, myText);

	highScoreFile.close();

	int score = stoi(myText);

	std::string scoreS = std::to_string(score);
	int width = 10;
	if (scoreS.length() < width) {
		scoreS = std::string(width - scoreS.length(), '0') + scoreS;
	}

	highScoreText->SetText(scoreS);
	highScore = score;
}

void InGameUI::AddScore(int scoreAdd)
{
	score += scoreAdd;

	std::string scoreS = std::to_string(score);
	int width = 10;
	if (scoreS.length() < width) {
		scoreS = std::string(width - scoreS.length(), '0') + scoreS;
	}

	playerScore->SetText(scoreS);
}

void InGameUI::ScorePopUp(int score, float x, float y)
{
	std::string name = std::to_string(scoreNum) + "scorePop";
	scoreNum++;

	TextRenderer* scorePop = CreateText(name, engineRef->GetFont("font8"), x, y, 8, 8);
	scorePop->SetText(std::to_string(score));

	scorePopUps[name] = scorePopUpLifeTime;
}

void InGameUI::UpdateScorePopUp(float deltaTime)
{
	for (auto it = scorePopUps.begin(); it != scorePopUps.end(); )
	{
		it->second -= deltaTime;

		if (it->second <= 0.0f)
		{
			auto trIt = textRenders.find(it->first);
			if (trIt != textRenders.end())
			{
				delete trIt->second;
				textRenders.erase(trIt);
			}

			it = scorePopUps.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void InGameUI::UpdateHealth(int currentHP)
{
	SpriteSheet* hpColors = engineRef->GetSpriteSheet("hpColors");

	if (currentHP <= 20)
	{
		hpBar->SetSprite(hpColors->GetSprite(2));
	}
	else if (currentHP <= 50)
	{
		hpBar->SetSprite(hpColors->GetSprite(1));
	}
	else
	{
		hpBar->SetSprite(hpColors->GetSprite(0));
	}


	float size = 192 * (currentHP/100.0f);

	if (size <= 0) size = 0;

	if (currentHP > 100)
	{
		hpBar->SetSize(192, 12);

		size -= 192;

		if (size > 192) size = 192;

		shieldBar->SetSize(size, 12);
	}
	else
	{
		hpBar->SetSize(size, 12);
		shieldBar->SetSize(0, 12);
	}

}

void InGameUI::SetLifes(int lifeAmmout)
{
	for (size_t i = 0; i < lifeAmmout; i++)
	{
		float x = 10 + (32 * i) + (10 * (i));

		std::string name = std::to_string(i) + "lifeIcon";

		Object* lifeIcon = CreateSprite(name, engineRef->GetSpriteSheet("shipIcon")->GetSprite(0), x, 410, 32, 32);
		lifes.push_back(lifeIcon);
	}
}

void InGameUI::RemoveLife()
{
	if (lifes.empty()) return;

	lifes.back()->Destroy();
	lifes.pop_back();
}


