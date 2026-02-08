#pragma once
#include <string>
#include <glad/glad.h>

class Texture
{
private:
    std::string filePath;
    GLuint textureID;
    int width, height;

    void LoadFromFile();

public:
    Texture(std::string path);
    ~Texture();

    GLuint GetTextureID() const { return textureID; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    void Bind(int slot = 0) const;
    void Unbind() const;
};
