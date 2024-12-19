#include "pch.h"
#include "AudioManager.h"

AudioManager* AudioManager::Get()
{
    static AudioManager mInstance;

    return &mInstance;
}

bool AudioManager::LoadSound(const char* name, const char* path) {
    SoundBuffer buffer;
    if (buffer.LoadFromFile(path)) {
        mSoundBuffers[name] = buffer;
        sf::Sound sound;
        sound.setBuffer(*mSoundBuffers[name].GetSoundBuffer());
        mSounds[name] = sound;
        return true;
    }
    return false;
}

void AudioManager::PlaySound(const char* name) {
    if (mSounds.find(name) != mSounds.end()) {
        mSounds[name].play();
    }
}

void AudioManager::StopSound(const char* name) {
    if (mSounds.find(name) != mSounds.end()) {
        mSounds[name].stop();
    }
}

void AudioManager::PlayMusic(const char* path) {
    if (mMusic.openFromFile(path)) {
        mMusic.play();
    }
}

void AudioManager::StopMusic() {
    mMusic.stop();
}

void AudioManager::SetSoundVolume(const char* name, float volume) {
    auto it = mSounds.find(name);
    if (it != mSounds.end()) {
        it->second.setVolume(volume);
    }
}

void AudioManager::SetMusicVolume(float volume) {
    mMusic.setVolume(volume);
}