#include "pch.h"
#include "AssetManager.h"
#include <iostream>

Texture* AssetManager::LoadTexture(const char* path)
{
	Texture* texture = new Texture(path);
	std::cout << "Loading texture: " << path << std::endl;
	mTextures[path] = *texture;

	return texture;
}

Texture* AssetManager::GetTexture(const char* path)
{
	auto it = mTextures.find(path);

	if (it == mTextures.end())
		return LoadTexture(path);
	else
		return &it->second;
}