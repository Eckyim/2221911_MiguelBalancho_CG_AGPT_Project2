#include "pch.h"
#include "Texture.h"
#include <SDL3/SDL.h>
#include <iostream>

Texture::Texture(std::string path)
{
    filePath = path;
    textureID = 0;
    width = 0;
    height = 0;

    LoadFromFile();
}

Texture::~Texture()
{
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

void Texture::LoadFromFile()
{
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
    if (surface == nullptr) {
        std::cout << "Failed to load image: " << filePath << " (" << SDL_GetError() << ")" << std::endl;
        return;
    }

    width = surface->w;
    height = surface->h;

    SDL_Surface* rgbaSurface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
    SDL_DestroySurface(surface);

    if (rgbaSurface == nullptr) {
        std::cout << "Failed to convert surface: " << filePath << std::endl;
        return;
    }

    Uint8* pixels = static_cast<Uint8*>(rgbaSurface->pixels);
    int pitch = rgbaSurface->pitch;
    for (int y = 0; y < rgbaSurface->h; ++y) {
        Uint8* row = pixels + y * pitch;
        for (int x = 0; x < rgbaSurface->w; ++x) {
            Uint8* px = row + x * 4;
            Uint8 r = px[0];
            Uint8 g = px[1];
            Uint8 b = px[2];


            if (r == 255 && g == 0 && b == 255) {
                px[3] = 0; 
            }
        }
    }


    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rgbaSurface->w, rgbaSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaSurface->pixels);

    SDL_DestroySurface(rgbaSurface);

    //std::cout << "Loaded OpenGL texture: " << filePath << " (" << width << "x" << height << ", ID: " << textureID << ")" << std::endl;
}

void Texture::Bind(int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}