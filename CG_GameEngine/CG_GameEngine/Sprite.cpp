#include "pch.h"

#include "Sprite.h"
#include "Texture.h"
#include "Rect.h"

Sprite::Sprite(Texture* sheet, int x, int y, int w, int h)
{
    spriteSheet = sheet;
    sourceRect = new Rect{ x, y, w, h };
}

Sprite::~Sprite()
{
    if (sourceRect != nullptr) {
        delete sourceRect;
        sourceRect = nullptr;
    }
}