#include "pch.h"
#include <iostream>
#include <SDL3/SDL.h>
#include "Input.h"

Input::Input()
{
    keyboardState = SDL_GetKeyboardState(nullptr);

    controller = nullptr;
}

Input::~Input()
{
    if (controller != nullptr) {
        SDL_CloseGamepad(controller);
        controller = nullptr;
    }
}

bool Input::GetKey(int key)
{
    return keyboardState[key];
}

bool Input::IsControllerConnected()
{
    if (controller == nullptr) {
        return false;
    }
    else
    {
        return true;
    }
}

bool Input::GetControllerButton(int button)
{
    if (!IsControllerConnected()) return false;

    return SDL_GetGamepadButton(controller, (SDL_GamepadButton)button);
}

float Input::GetControllerAxis(int axis)
{
    if (!IsControllerConnected()) return 0.0f;

    int value = SDL_GetGamepadAxis(controller, (SDL_GamepadAxis)axis);

    return value / 32767.0f;
}

void Input::OnControllerAdded(int deviceID)
{
    if (!IsControllerConnected()) {
        controller = SDL_OpenGamepad(deviceID);
        if (controller) {
            std::cout << "Controller connected: " << SDL_GetGamepadName(controller) << std::endl;
        }
    }
}

void Input::OnControllerRemoved(int deviceID)
{
    if (IsControllerConnected()) {
        SDL_JoystickID id = SDL_GetGamepadID(controller);
        if (id == deviceID) {
            SDL_CloseGamepad(controller);
            controller = nullptr;
            std::cout << "Controller disconnected" << std::endl;
        }
    }
}