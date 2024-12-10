#include "pch.h"
#include "Texture.h"

Texture::Texture(const char* path)
{
	mTexture.loadFromFile(path);
}

Texture::~Texture()
{
}

sf::Texture* Texture::GetTexture()
{
	return &mTexture;
}