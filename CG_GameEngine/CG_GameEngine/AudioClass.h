#pragma once
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL.h>
#include <map>
#include <string>
#include <vector>

class SoundClass;

class AudioClass
{
private:
    SDL_AudioDeviceID deviceID;
    SDL_AudioSpec outputSpec;

    std::map<std::string, SoundClass*> sounds;
    std::vector<SDL_AudioStream*> activeStreams;

    bool initialized;

public:
    AudioClass();
    ~AudioClass();

    void Update();

    SoundClass* LoadSound(std::string name, std::string filepath);
    SoundClass* GetSound(std::string name);

    void PlaySound(std::string name);

    void CleanupFinishedStreams();

    void StopAll();

    SDL_AudioDeviceID GetDeviceID() { return deviceID; }
    SDL_AudioSpec GetOutputSpec() { return outputSpec; }
};