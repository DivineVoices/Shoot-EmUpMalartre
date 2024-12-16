#include "pch.h"
#include "AssetManager.h"
#include "Texture.h"
#include <iostream>

Texture* AssetManager::LoadTexture(std::string path)
{
	Texture* texture = new Texture(path);
	std::cout << "Loading texture: " << path << std::endl;
	mTextures[path] = texture;

	return texture;
}

Texture* AssetManager::GetTexture(std::string path)
{
	auto it = mTextures.find(path);

	if (it == mTextures.end())
		return LoadTexture(path);
	else
		return it->second;
}

AssetManager* AssetManager::Get()
{
	static AssetManager mInstance;

	return &mInstance;
}