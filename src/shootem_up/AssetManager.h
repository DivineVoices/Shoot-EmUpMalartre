#pragma once
#include "Texture.h"

class AssetManager
{
	std::map<const char*, Texture> mTextures;

private:
	Texture* LoadTexture(const char* path);

public:
	Texture* GetTexture(const char* path);
};