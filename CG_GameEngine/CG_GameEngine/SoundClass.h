#pragma once
#include <string>
#include <SDL3/SDL_audio.h>

class SoundClass
{
private:
    SDL_AudioSpec originalSpec;
    SDL_AudioSpec convertedSpec;
    Uint8* originalBuffer;
    Uint8* convertedBuffer;
    Uint32 originalLength;
    Uint32 convertedLength;
    bool converted;

public:
    SoundClass(std::string path);
    ~SoundClass();

    bool ConvertTo(SDL_AudioSpec targetSpec);


    SDL_AudioSpec GetSpec() { return converted ? convertedSpec : originalSpec; }
    Uint8* GetBuffer() { return converted ? convertedBuffer : originalBuffer; }
    Uint32 GetBufferLength() { return converted ? convertedLength : originalLength; }
};