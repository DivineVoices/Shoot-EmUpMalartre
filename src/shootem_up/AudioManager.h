#pragma once
#include <map>
#include <string>
#include <SFML/Audio.hpp>
#include "SoundBuffer.h"

class AudioManager {
    std::map<const char*, SoundBuffer> mSoundBuffers;
    std::map<const char*, sf::Sound> mSounds;
    sf::Music mMusic;

public:
    static AudioManager* Get();
    AudioManager() = default;
    ~AudioManager() = default;

    bool LoadSound(const char* name, const char* path);
    void PlaySound(const char* name);
    void StopSound(const char* name);
    void PlayMusic(const char* path);
    void StopMusic();

    void SetSoundVolume(const char* name, float volume);
    void SetMusicVolume(float volume);
};  