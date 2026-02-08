#pragma once
#include <string>
#include "TextSpriteSheet.h"

class MyGameEngine;

class TextRenderer
{
private:
    MyGameEngine* engineRef;
    TextSpriteSheet* fontSheet;
    
    std::string text;

    float characterSpacing;
    float lineHeight;
    bool isCentered;

    float xPos;
    float yPos;

    float charWidth;
    float charHeight;
public:
    TextRenderer(MyGameEngine* engine, TextSpriteSheet* font, float x, float y, float cWidth, float cHeight);

    void RenderText();

    void RenderTextCentered();
    float CalculateTextWidth();

    void SetText(std::string txt) { text = txt; }

    void SetCharacterSpacing(float spacing) { characterSpacing = spacing; }
    void SetLineHeight(float height) { lineHeight = height; }
    void SetCentered(bool centered) { isCentered = centered; }

    void SetPosition(float x, float y);
    void SetCharSize(float w, float h);
};