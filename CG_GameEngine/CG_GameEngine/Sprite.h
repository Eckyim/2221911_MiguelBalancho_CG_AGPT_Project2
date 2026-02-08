#pragma once

class Texture;
class Rect;

class Sprite {
private:
    Texture* spriteSheet;
    Rect* sourceRect;

public:
    Sprite(Texture* sheet, int x, int y, int w, int h);
    ~Sprite();

    Texture* GetTexture() const { return spriteSheet; }
    Rect* GetSourceRect() const { return sourceRect; }
};
