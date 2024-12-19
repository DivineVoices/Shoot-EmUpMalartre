#pragma once
#include <SFML/Audio.hpp>

class SoundBuffer {
    sf::SoundBuffer mSoundBuffer;
public:
    SoundBuffer() = default;
    SoundBuffer(const char* path);
    ~SoundBuffer() = default;

    bool LoadFromFile(const char* path);
    sf::SoundBuffer* GetSoundBuffer();
};