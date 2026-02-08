#include "pch.h"
#include <glad/glad.h>
#include <iostream>
#include "Window.h"

Window::Window(std::string name, int w, int h)
{
    width = w;
    height = h;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(name.c_str(), w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (window == nullptr) {
        std::cout << "Window creation Error" << std::endl;
        return;
    }

    glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr) {
        std::cout << "OpenGL context creation failed" << std::endl;
        return;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "GLAD initialization failed" << std::endl;
        return;
    }

    SDL_GL_SetSwapInterval(1);

    glViewport(0, 0, width, height);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Window::~Window()
{
    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void Window::SetSize(int w, int h)
{
    width = w;
    height = h;
}

void Window::SwapBuffers()
{
    SDL_GL_SwapWindow(window);
}