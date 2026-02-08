#include "pch.h"
#include "SoundClass.h"
#include <iostream>

SoundClass::SoundClass(std::string path)
{
    originalBuffer = nullptr;
    convertedBuffer = nullptr;
    originalLength = 0;
    convertedLength = 0;
    converted = false;

    if (!SDL_LoadWAV(path.c_str(), &originalSpec, &originalBuffer, &originalLength)) {
        std::cerr << "Failed to load WAV file: " << path << " - " << SDL_GetError() << std::endl;
        return;
    }
}

SoundClass::~SoundClass()
{
    if (originalBuffer != nullptr) {
        SDL_free(originalBuffer);
        originalBuffer = nullptr;
    }

    if (convertedBuffer != nullptr) {
        delete[] convertedBuffer;
        convertedBuffer = nullptr;
    }
}

bool SoundClass::ConvertTo(SDL_AudioSpec targetSpec)
{
    if (originalSpec.freq == targetSpec.freq &&
        originalSpec.format == targetSpec.format &&
        originalSpec.channels == targetSpec.channels) {
        std::cout << "Sound already in target format, no conversion needed" << std::endl;
        return true;
    }

    SDL_AudioStream* converter = SDL_CreateAudioStream(&originalSpec, &targetSpec);
    if (!converter) {
        std::cerr << "Failed to create converter: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!SDL_PutAudioStreamData(converter, originalBuffer, originalLength)) {
        std::cerr << "Failed to put data in converter: " << SDL_GetError() << std::endl;
        SDL_DestroyAudioStream(converter);
        return false;
    }

    SDL_FlushAudioStream(converter);

    convertedLength = SDL_GetAudioStreamAvailable(converter);
    if (convertedLength <= 0) {
        std::cerr << "No converted data available" << std::endl;
        SDL_DestroyAudioStream(converter);
        return false;
    }

    convertedBuffer = new Uint8[convertedLength];

    int bytesRead = SDL_GetAudioStreamData(converter, convertedBuffer, convertedLength);
    if (bytesRead != convertedLength) {
        std::cerr << "Failed to read all converted data" << std::endl;
        delete[] convertedBuffer;
        convertedBuffer = nullptr;
        SDL_DestroyAudioStream(converter);
        return false;
    }

    convertedSpec = targetSpec;
    converted = true;

    SDL_DestroyAudioStream(converter);

    return true;
}