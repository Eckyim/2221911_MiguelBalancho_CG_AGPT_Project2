#include "pch.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "RenderingClass.h"
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"
#include "Rect.h"
#include "Object.h"
#include "UIClass.h"

RenderingClass::RenderingClass(Window* getwindow)
{
    window = getwindow;

    projection = glm::ortho(
        0.0f,
        (float)window->GetWindowWidth(),
        (float)window->GetWindowHeight(),
        0.0f,  
        -1.0f,
        1.0f
    );

    InitShaders();
    InitQuad();

   // std::cout << "OpenGL Renderer initialized" << std::endl;
}

RenderingClass::~RenderingClass()
{
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);

    if (spriteShader != nullptr) {
        delete spriteShader;
        spriteShader = nullptr;
    }
}

void RenderingClass::InitShaders()
{
    spriteShader = new Shader(
        "..\\..\\CG_GameEngine\\CG_GameEngine\\shaders\\spriteVertex.glsl",
        "..\\..\\CG_GameEngine\\CG_GameEngine\\shaders\\spriteFragment.glsl"
    );
}

void RenderingClass::InitQuad()
{
    float vertices[] = {
              
        0.0f, 1.0f, 0.0f, 1.0f,  
        1.0f, 0.0f, 1.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,  
        1.0f, 1.0f, 1.0f, 1.0f,  
        1.0f, 0.0f, 1.0f, 0.0f   
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quadVAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void RenderingClass::ClearFrame()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderingClass::ShowFrame()
{
    window->SwapBuffers();
}

void RenderingClass::DrawSprite(Sprite* sprite, Rect* rectangle)
{
    if (sprite == nullptr || rectangle == nullptr) return;

    Texture* texture = sprite->GetTexture();
    Rect* srcRect = sprite->GetSourceRect();

    float texOffsetX = srcRect->GetX() / (float)texture->GetWidth();
    float texOffsetY = srcRect->GetY() / (float)texture->GetHeight();
    float texSizeX = srcRect->GetW() / (float)texture->GetWidth();
    float texSizeY = srcRect->GetH() / (float)texture->GetHeight();


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(rectangle->GetX(), rectangle->GetY(), 0.0f));
    if (rectangle->GetRotation() != 0)
    {
        model = glm::translate(model, glm::vec3(rectangle->GetW() * 0.5f, rectangle->GetH() * 0.5f, 0.0f));
        model = glm::rotate(model, rectangle->GetRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-rectangle->GetW() * 0.5f, -rectangle->GetH() * 0.5f, 0.0f));
        model = glm::scale(model, glm::vec3(rectangle->GetW(), rectangle->GetH(), 1.0f));
    }
    else
    {
        model = glm::scale(model, glm::vec3(rectangle->GetW(), rectangle->GetH(), 1.0f));
    }


    spriteShader->use();
    spriteShader->setMat4("projection", projection);
    spriteShader->setMat4("model", model);
    spriteShader->setVec2("texOffset", glm::vec2(texOffsetX, texOffsetY));
    spriteShader->setVec2("texSize", glm::vec2(texSizeX, texSizeY));
    spriteShader->setInt("spriteTexture", 0);

    texture->Bind(0);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void RenderingClass::DrawTexture(Texture* texture, Rect* rectangle)
{
    if (texture == nullptr || rectangle == nullptr) return;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(rectangle->GetX(), rectangle->GetY(), 0.0f));
    model = glm::scale(model, glm::vec3(rectangle->GetW(), rectangle->GetH(), 1.0f));

    spriteShader->use();
    spriteShader->setMat4("projection", projection);
    spriteShader->setMat4("model", model);
    spriteShader->setVec2("texOffset", glm::vec2(0.0f, 0.0f));
    spriteShader->setVec2("texSize", glm::vec2(1.0f, 1.0f));
    spriteShader->setInt("spriteTexture", 0);

    texture->Bind(0);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void RenderingClass::DrawTextureFullScreen(Texture* texture)
{
    if (texture == nullptr) return;

    Rect fullScreen(0, 0, window->GetWindowWidth(), window->GetWindowHeight());
    DrawTexture(texture, &fullScreen);
}

void RenderingClass::DrawObject(Object* object)
{
    if (object == nullptr) return;
    object->Render();
}

void RenderingClass::DrawUI(UIClass* ui)
{
    if (ui == nullptr) return;
    ui->Render();
}
