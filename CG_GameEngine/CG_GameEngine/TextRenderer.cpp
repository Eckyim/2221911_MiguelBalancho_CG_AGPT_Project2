#include "pch.h"
#include "TextRenderer.h"
#include "TextSpriteSheet.h"
#include "CG_GameEngine.h"
#include "RenderingClass.h"
#include "Sprite.h"
#include "Rect.h"
#include <sstream>

TextRenderer::TextRenderer(MyGameEngine* engine, TextSpriteSheet* font, float x, float y, float cWidth, float cHeight)
{
    engineRef = engine;
    fontSheet = font;

    xPos = x;
    yPos = y;
    charWidth = cWidth;
    charHeight = cHeight;

    isCentered = false;
    characterSpacing = 2.0f;
    lineHeight = 1.5f;

    text = "sample text";
}

void TextRenderer::RenderText()
{

    float currentX = xPos;
    float currentY = yPos;
    RenderingClass* renderer = engineRef->GetRenderer();

    if (isCentered)
    {
        float textWidth = CalculateTextWidth();
        currentX = xPos - (textWidth / 2.0f);
    }

    for (char c : text) {
        if (c == '\n') {
            currentX = xPos;
            currentY += charHeight * lineHeight;
            continue;
        }

        Sprite* charSprite = fontSheet->GetCharacterSprite(c);
        if (charSprite != nullptr) {
            Rect charRect(currentX, currentY, charWidth, charHeight);
            renderer->DrawSprite(charSprite, &charRect);
        }
        currentX += charWidth + characterSpacing;
    }
}

void TextRenderer::RenderTextCentered()
{

    RenderText();
}

float TextRenderer::CalculateTextWidth()
{
    int visibleChars = 0;
    for (char c : text) {
        if (c != '\n') visibleChars++;
    }

    return (visibleChars * charWidth) + ((visibleChars - 1) * characterSpacing);
}

void TextRenderer::SetPosition(float x, float y)
{
    xPos = x;
    yPos = y;
}

void TextRenderer::SetCharSize(float w, float h)
{
    charWidth = w;
    charHeight = h;
}