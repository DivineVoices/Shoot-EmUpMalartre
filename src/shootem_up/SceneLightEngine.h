#pragma once

class GameManagerLightEngine;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

class SceneLightEngine
{
private:
	GameManagerLightEngine* mpGameManager;

private:
	void SetGameManager(GameManagerLightEngine* pGameManager) { mpGameManager = pGameManager; }
	
protected:
	SceneLightEngine() = default;

	virtual void OnInitialize() = 0;
	virtual void OnEvent(const sf::Event& event) = 0;
	virtual void OnUpdate() = 0;

public:
	template<typename T>
	T* CreateEntity(float radius, const sf::Color& color);

	float GetDeltaTime() const;

	int GetWindowWidth() const;
	int GetWindowHeight() const;

	friend GameManagerLightEngine;
};

#include "SceneLightEngine.inl"