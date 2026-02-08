#pragma once

#include <SDL3/SDL.h> 

class Event
{
private:
    SDL_Event event;

public:
    Event();


    bool VerifyType(SDL_EventType type);
    SDL_Event* GetSDLEvent() { return &event; }


    int GetGamepadDeviceID();
};

