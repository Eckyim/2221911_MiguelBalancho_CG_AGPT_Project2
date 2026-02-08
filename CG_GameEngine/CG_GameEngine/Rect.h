#pragma once

#include <SDL3/SDL.h> 

class Rect {
private:
    SDL_FRect rectangle;
    SDL_Rect intRectangle;

    float rotation = 0.0f;
public:

    Rect(float x, float y, float w, float h);
    Rect(int x, int y, int w, int h);

    void SetPosition(float x, float y);
    void SetSize(float w, float h);

    float GetRotation() const { return rotation; }
    void SetRotation(float r) { rotation = r; }

    //SDL_Rect GetSDLRect() { return intRectangle; }
    //SDL_FRect GetSDLFRect() { return rectangle; }
    SDL_Rect* GetSDLRectPtr() { return &intRectangle; }
    SDL_FRect* GetSDLFRectPtr() { return &rectangle; }

    float GetX() const { return rectangle.x; }
    float GetY() const { return rectangle.y; }
    float GetW() const { return rectangle.w; }
    float GetH() const { return rectangle.h; }
};

