#pragma once

#include <list>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

class Entity;
class Scene;
class Debug;

namespace sf
{
	class RenderWindow;
	class Event;
}

class GameManager
{

private:
	GameManager();

	 virtual void Run() = 0;

	 virtual void HandleInput() = 0;
	 virtual void Update() = 0;
	 virtual void Draw() = 0;

	 virtual void SetDeltaTime(float deltaTime) = 0;

	 virtual sf::RenderWindow* GetWindow() const = 0;

public:

	 virtual void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60) = 0;

	 virtual float GetDeltaTime() const = 0;
	 virtual Scene* GetScene() const = 0;
	 virtual sf::Font& GetFont() = 0;

};