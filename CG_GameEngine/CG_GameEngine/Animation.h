#pragma once

#include <vector>
#include <string>

class Sprite;
class SpriteSheet;

class Animation {
private:
    std::string name;
    std::vector<Sprite*> frames;
    int currentFrame;
    float frameTime;
    float elapsedTime;
    bool isLooping;
    bool isPlaying;

public:
    Animation(std::string n, SpriteSheet* sheet, int startIndex, int endIndex, bool loop, float framelenght);
    Animation(std::string n, SpriteSheet* sheet, std::vector<int> indices, bool loop, float framelenght);
    ~Animation();

    void Play();
    void Pause();
    void Stop(); 
    void SetFrameTime(float time) { frameTime = time; }


    void Update(float deltaTime);

    Sprite* GetCurrentSprite() { return frames[currentFrame]; }
    Animation* Clone();

    bool IsPlaying() const { return isPlaying; }
    std::string GetName() const { return name; }
    int GetCurrentFrameIndex() const { return currentFrame; }

private:
    void PrepareFrames(SpriteSheet* sheet, std::vector<int> indices);

};