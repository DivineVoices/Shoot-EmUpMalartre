#pragma once
#include <SFML/Graphics.hpp>

class Texture {
    sf::Texture mTexture;
public:
    Texture() = default;
    Texture(const char* path);
    ~Texture();
    sf::Texture* GetTexture();
};