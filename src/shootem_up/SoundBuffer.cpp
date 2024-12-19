#include "pch.h"
#include "SoundBuffer.h"

SoundBuffer::SoundBuffer(const char* path) {
    LoadFromFile(path);
}

bool SoundBuffer::LoadFromFile(const char* path) {
    return mSoundBuffer.loadFromFile(path);
}

sf::SoundBuffer* SoundBuffer::GetSoundBuffer() {
    return &mSoundBuffer;
}