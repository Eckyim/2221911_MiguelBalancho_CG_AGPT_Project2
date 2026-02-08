#pragma once
#include <string>
#include <SDL3/SDL.h>

class Window
{
private:
	SDL_Window* window;
    SDL_GLContext glContext;
    int width, height;

public:
    Window(std::string name, int w, int h);
    ~Window();


    SDL_Window* GetSDLWindow() { return window; }
    SDL_GLContext GetGLContext() { return glContext; }
    int GetWindowWidth() { return width; }
    int GetWindowHeight() { return height; }

    void SetSize(int w, int h);

    void SwapBuffers();
	
};

