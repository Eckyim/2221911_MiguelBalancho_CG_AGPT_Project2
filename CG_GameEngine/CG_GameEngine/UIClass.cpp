#include "pch.h"
#include "CG_GameEngine.h"
#include "UIClass.h"

UIClass::UIClass(MyGameEngine* engine)
{
    engineRef = engine;
    engineRef->AddUI(this);
}

UIClass::~UIClass()
{
    for (auto& pair : textRenders) {
        delete pair.second;
    }
    textRenders.clear();

    for (auto& pair : sprites) {
        delete pair.second;
    }
    sprites.clear();
}

void UIClass::Render()
{

    for (auto it = sprites.begin(); it != sprites.end(); )
    {
        Object* obj = it->second;
        obj->Render();

        if (obj->GetToDestroy())
        {
            // delete the object and erase the map entry, advancing the iterator safely
            delete obj;
            it = sprites.erase(it);
        }
        else
        {
            ++it;
        }
    }


    //for (auto& pair : sprites) {
    //    pair.second->Render();

    //    if (pair.second->GetToDestroy())
    //    {
    //        RemoveSprite(pair.first);
    //    }
    //}

    for (auto& pair : textRenders) {
        pair.second->RenderText();
    }
}

TextRenderer* UIClass::CreateText(std::string name, TextSpriteSheet* font, float x, float y, float cWidth, float cHeight)
{
    TextRenderer* newText = new TextRenderer(engineRef, font, x, y, cWidth, cHeight);

    textRenders[name] = newText;
    return newText;
}

TextRenderer* UIClass::GetText(std::string name)
{
    auto it = textRenders.find(name);
    if (it != textRenders.end()) {
        return it->second;
    }

    return nullptr;
}

Object* UIClass::CreateSprite(std::string name, Sprite* sprt, float x, float y, float w, float h)
{
    Object* nSprite = new Object(sprt, x, y, w, h);
    nSprite->SetRenderer(engineRef->GetRenderer());
    sprites[name] = nSprite;
    return nSprite;
}

Object* UIClass::GetSprite(std::string name)
{
    auto it = sprites.find(name);
    if (it != sprites.end()) {
        return it->second;
    }

    return nullptr;
}

void UIClass::RemoveSprite(std::string name)
{
    //sprites.erase(name);

    auto it = sprites.find(name);
    if (it != sprites.end()) {
        delete it->second;    // free owned Object
        sprites.erase(it);    // erase by iterator (no double-delete)
    }
}


void UIClass::SetUp()
{
}

void UIClass::OnUpdate(float deltaTime)
{
}

void UIClass::OnEnd()
{
}
