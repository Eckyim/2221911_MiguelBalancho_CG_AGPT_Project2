#pragma once
#include <string>
#include <map>
#include <vector>

class Texture;
class Sprite;
class Animation;

class SpriteSheet {
protected:
    Texture* texture;
    std::vector<Sprite*> sprites;
    int spriteWidth, spriteHeight;
    int columns, rows;
    std::map<std::string, Animation*> animations;

public:
    SpriteSheet(std::string filePath, int col, int row);
    ~SpriteSheet();

    Sprite* GetSprite(int index);
    Sprite* GetSprite(int col, int row);
    Sprite* CreateCustomSprite(int x, int y, int width, int height);

    void CutSpriteSheet();
    std::string CreateAnimation(std::string n, int startIndex, int endIndex, bool loop, float framelenght);
    std::string CreateAnimation(std::string n, std::vector<int> indices, bool loop, float framelenght);

    std::vector<Sprite*> GetAllSprites() { return sprites; }
    Animation* GetAnimation(std::string n);
    std::map<std::string, Animation*> GetAllAnimations() { return animations; }

    int GetSpriteCount() const { return sprites.size(); }
    int GetColumns() const { return columns; }
    int GetRows() const { return rows; }
    Texture* GetTexture() const { return texture; }
};