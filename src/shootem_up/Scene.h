#pragma once

class GameManager;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

class Scene
{
private:
	GameManager* mpGameManager;

private:
	virtual void SetGameManager(GameManager* pGameManager) = 0;

protected:
	Scene() = default;

	virtual void OnInitialize() = 0;
	virtual void OnEvent(const sf::Event& event) = 0;
	virtual void OnUpdate() = 0;

public:

	virtual float GetDeltaTime() const = 0;

	virtual int GetWindowWidth() const = 0;
	virtual int GetWindowHeight() const = 0;
};