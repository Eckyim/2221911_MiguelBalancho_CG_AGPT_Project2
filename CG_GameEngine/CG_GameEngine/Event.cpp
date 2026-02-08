#include "pch.h"
#include "Event.h"


Event::Event()
{
    event = SDL_Event();
}

bool Event::VerifyType(SDL_EventType type)
{
	if (event.type == type)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

int Event::GetGamepadDeviceID()
{
	if (event.type == SDL_EVENT_GAMEPAD_ADDED ||
		event.type == SDL_EVENT_GAMEPAD_REMOVED) {
		return event.gdevice.which;
	}

	return -1;
}