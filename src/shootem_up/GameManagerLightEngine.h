#pragma once

#include <list>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#include "GameManager.h"

class EntityLightEngine;
class SceneLightEngine;
class Debug;

namespace sf 
{
	class RenderWindow;
	class Event;
}

class GameManagerLightEngine : public GameManager
{
	std::list<EntityLightEngine*> mEntities;
	std::list<EntityLightEngine*> mEntitiesToDestroy;
	std::list<EntityLightEngine*> mEntitiesToAdd;

	sf::RenderWindow* mpWindow;
	sf::Font mFont;

	SceneLightEngine* mpScene;

	float mDeltaTime;

	int mWindowWidth;
	int mWindowHeight;

private:
	GameManagerLightEngine();

	void Run() override;
	
	void HandleInput() override;
	void Update() override;
	void Draw() override;

	void SetDeltaTime(float deltaTime) override { mDeltaTime = deltaTime; }

	sf::RenderWindow* GetWindow() const override { return mpWindow; }

public:
	~GameManagerLightEngine();
	static GameManagerLightEngine* Get();

	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60) override;

	template<typename T>
	void LaunchScene();

	float GetDeltaTime() const override { return mDeltaTime; }
	SceneLightEngine* GetScene() const override { return mpScene; }
	sf::Font& GetFont() override { return mFont; };

	friend Debug;
	friend Scene;
};

#include "GameManagerLightEngine.inl"