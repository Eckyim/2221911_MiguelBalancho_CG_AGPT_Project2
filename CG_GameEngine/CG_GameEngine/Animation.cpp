#include "pch.h"

#include <iostream>

#include "Animation.h"
#include "SpriteSheet.h"
#include "Sprite.h"
#include "SoundClass.h"


Animation::Animation(std::string n, SpriteSheet* sheet, int startIndex, int endIndex, bool loop, float framelenght)
{
	name = n;
	frameTime = framelenght;
	isLooping = loop;

	//std::cout << name << " frames: ";
	std::vector<int> indices;
	if (endIndex > startIndex)
	{
		for (int i = startIndex; i <= endIndex; i++)
		{
			//std::cout << i << ", ";
			indices.push_back(i);
		}
	}
	else
	{
		for (int i = startIndex; i >= endIndex; i--)
		{
			//std::cout << i << ", ";
			indices.push_back(i);
		}
	}
	//std::cout << std::endl;

	PrepareFrames(sheet, indices);
}

Animation::Animation(std::string n, SpriteSheet* sheet, std::vector<int> indices, bool loop, float framelenght)
{
	name = n;
	frameTime = framelenght;
	isLooping = loop;

	PrepareFrames(sheet, indices);
}


Animation::~Animation()
{
	frames.clear();
}

void Animation::PrepareFrames(SpriteSheet* sheet, std::vector<int> indices)
{
	if (sheet == nullptr) return;

	for (int index : indices) {
		Sprite* sprite = sheet->GetSprite(index);
		if (sprite != nullptr) {
			frames.push_back(sprite);
		}
	}
}

void Animation::Play()
{
	isPlaying = true;
}

void Animation::Pause()
{
	isPlaying = false;
}
                
void Animation::Stop()
{
	isPlaying = false;
	currentFrame = 0;
	elapsedTime = 0.0f;
}

void Animation::Update(float deltaTime)
{
	if (!isPlaying || frames.empty()) return;

	elapsedTime += deltaTime;

	if (elapsedTime >= frameTime) {
		elapsedTime = 0.0f;
		currentFrame++;

		if (currentFrame >= frames.size()) {
			if (isLooping) {
				currentFrame = 0;
			}
			else {
				currentFrame = frames.size() - 1;
				isPlaying = false;
			}
		}
	}
}

Animation* Animation::Clone()
{
	Animation* clone = new Animation(name, nullptr, {}, isLooping, frameTime);

	clone->frames = this->frames;
	clone->currentFrame = 0;
	clone->elapsedTime = 0.0f;
	clone->isPlaying = false;

	return clone;
}
