#include "pch.h"
#include "AudioClass.h"
#include "SoundClass.h"
#include <iostream>
#include "CG_GameEngine.h"

AudioClass::AudioClass()
{
    initialized = false;
    deviceID = 0;

    SDL_zero(outputSpec);
    outputSpec.freq = 44100;
    outputSpec.format = SDL_AUDIO_S16;
    outputSpec.channels = 2;

    deviceID = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &outputSpec);

    if (deviceID == 0) {
        std::cerr << "Failed to open audio device: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_ResumeAudioDevice(deviceID);

    initialized = true;
}

AudioClass::~AudioClass()
{
    StopAll();

    for (auto& pair : sounds) {
        delete pair.second;
    }
    sounds.clear();

    if (deviceID) {
        SDL_CloseAudioDevice(deviceID);
        deviceID = 0;
    }
}

void AudioClass::Update()
{
    CleanupFinishedStreams();
}

SoundClass* AudioClass::LoadSound(std::string name, std::string filepath)
{
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        std::cout << "Sound '" << name << "' already loaded" << std::endl;
        return it->second;
    }

    SoundClass* sound = new SoundClass(filepath);
    if (sound->GetBuffer() == nullptr) {
        std::cerr << "Failed to load sound '" << name << "'" << std::endl;
        delete sound;
        return nullptr;
    }

    if (!sound->ConvertTo(outputSpec)) {
        std::cerr << "Failed to convert sound '" << name << "' to output format" << std::endl;
        delete sound;
        return nullptr;
    }

    sounds[name] = sound;
    return sound;
}

SoundClass* AudioClass::GetSound(std::string name)
{
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        return it->second;
    }

    std::cerr << "Sound '" << name << "' not found!" << std::endl;
    return nullptr;
}

void AudioClass::PlaySound(std::string name)
{
    if (!initialized) {
        std::cerr << "AudioClass not initialized!" << std::endl;
        return;
    }

    SoundClass* sound = GetSound(name);
    if (sound == nullptr) return;

    SDL_AudioStream* stream = SDL_CreateAudioStream(&outputSpec, &outputSpec);
    if (!stream) {
        std::cerr << "Failed to create audio stream: " << SDL_GetError() << std::endl;
        return;
    }

    if (!SDL_BindAudioStream(deviceID, stream)) {
        std::cerr << "Failed to bind audio stream: " << SDL_GetError() << std::endl;
        SDL_DestroyAudioStream(stream);
        return;
    }

    if (!SDL_PutAudioStreamData(stream, sound->GetBuffer(), sound->GetBufferLength())) {
        std::cerr << "Failed to put audio stream data: " << SDL_GetError() << std::endl;
        SDL_DestroyAudioStream(stream);
        return;
    }

    activeStreams.push_back(stream);
}

void AudioClass::CleanupFinishedStreams()
{
    for (auto it = activeStreams.begin(); it != activeStreams.end(); ) {
        SDL_AudioStream* stream = *it;

        int available = SDL_GetAudioStreamAvailable(stream);

        if (available <= 0) {
            SDL_UnbindAudioStream(stream);
            SDL_DestroyAudioStream(stream);
            it = activeStreams.erase(it);
        }
        else {
            ++it;
        }
    }
}

void AudioClass::StopAll()
{
    for (SDL_AudioStream* stream : activeStreams) {
        SDL_UnbindAudioStream(stream);
        SDL_DestroyAudioStream(stream);
    }
    activeStreams.clear();
}