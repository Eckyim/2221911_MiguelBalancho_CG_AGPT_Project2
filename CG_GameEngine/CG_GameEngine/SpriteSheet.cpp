#include "pch.h"
#include <iostream>
#include "SpriteSheet.h"
#include "Texture.h"
#include "Sprite.h" 
#include "Animation.h"

SpriteSheet::SpriteSheet(std::string filePath, int col, int row)
{
    texture = new Texture(filePath);
    rows = row;
    columns = col;

    spriteWidth = texture->GetWidth() / col;
    spriteHeight = texture->GetHeight() / row;

    CutSpriteSheet();
}

SpriteSheet::~SpriteSheet()
{
    for (Sprite* sprite : sprites) {
        delete sprite;
    }
    sprites.clear();

    if (texture != nullptr) {
        delete texture;
        texture = nullptr;
    }

    for (auto& pair : animations) {
        delete pair.second;
    }
    animations.clear();
}

void SpriteSheet::CutSpriteSheet()
{
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            int x = col * spriteWidth;
            int y = row * spriteHeight;

            Sprite* sprite = new Sprite(texture, x, y, spriteWidth, spriteHeight);
            sprites.push_back(sprite);
        }
    }
}

Sprite* SpriteSheet::GetSprite(int index)
{
    if (index >= 0 && index < sprites.size()) {
        return sprites[index];
    }
    return nullptr;
}

Sprite* SpriteSheet::GetSprite(int col, int row)
{
    int index = row * columns + col;
    return GetSprite(index);
}

Sprite* SpriteSheet::CreateCustomSprite(int x, int y, int width, int height)
{
    Sprite* sprite = new Sprite(texture, x, y, width, height);
    sprites.push_back(sprite);
    return sprite;
}

std::string SpriteSheet::CreateAnimation(std::string n, int startIndex, int endIndex, bool loop, float framelenght)
{
    auto it = animations.find(n);
    if (it != animations.end()) {
        std::cout << "Warning: Animation '" << n << "' already exists" << std::endl;
        return "";
    }

    Animation* anim = new Animation(n, this, startIndex, endIndex, loop, framelenght);
    animations.insert({ n, anim });
    return n;
}

std::string SpriteSheet::CreateAnimation(std::string n, std::vector<int> indices, bool loop, float framelenght)
{
    auto it = animations.find(n);
    if (it != animations.end()) {
        std::cout << "Warning: Animation '" << n << "' already exists" << std::endl;
        return "";
    }

    Animation* anim = new Animation(n, this, indices, loop, framelenght);
    animations.insert({ n, anim });
    return n;
}

Animation* SpriteSheet::GetAnimation(std::string n)
{
    auto it = animations.find(n);
    if (it != animations.end()) {
        return it->second;
    }
    return nullptr;
}
