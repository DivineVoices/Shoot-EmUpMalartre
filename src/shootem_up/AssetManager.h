#pragma once
#include <map>
#include <string>

class Texture;

class AssetManager
{
	std::map<std::string, Texture* > mTextures;

public:
	Texture* LoadTexture(std::string path);

	static AssetManager* Get();

	Texture* GetTexture(std::string path);
};