#include "pch.h"
#include "Texture.h"

Texture::Texture(std::string path)
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