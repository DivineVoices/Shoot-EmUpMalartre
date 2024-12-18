#pragma once
#include <SFML/Graphics.hpp>

class Texture {
    sf::Texture mTexture;
public:
    Texture() = default;
    Texture(std::string path);
    ~Texture();
    sf::Texture* GetTexture();
};