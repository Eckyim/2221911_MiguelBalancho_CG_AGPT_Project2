#pragma once
#include "SpriteSheet.h"

class TextSpriteSheet : public  SpriteSheet
{
private:
    std::map<char, int> charToIndex;  
public:
	TextSpriteSheet(std::string filePath, int col, int row);

    void InitializeCharacterMap();

    Sprite* GetCharacterSprite(char c);
    bool HasCharacter(char c) const;
};