#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class Window;
class Texture;
class Sprite;
class Rect;
class Object;
class UIClass;
class Shader;

class RenderingClass {
private:
    Window* window;
    Shader* spriteShader;

    GLuint quadVAO, quadVBO;
    glm::mat4 projection;

    void InitQuad();         
    void InitShaders();        

public:
    RenderingClass(Window* getwindow);
    ~RenderingClass();

    void ClearFrame();
    void ShowFrame();

    void DrawTexture(Texture* texture, Rect* rectangle);
    void DrawTextureFullScreen(Texture* texture);
    void DrawObject(Object* object);
    void DrawUI(UIClass* ui);
    void DrawSprite(Sprite* sprite, Rect* rectangle);

    glm::mat4 GetProjection() const { return projection; }
    Shader* GetShader() const { return spriteShader; }
};
