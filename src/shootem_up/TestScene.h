#pragma once

#include "Scene.h"

class DummyEntity;

class TestScene : public Scene
{
	DummyEntity* pEntity1;
	DummyEntity* pEntity2;
	DummyEntity* pEntity3;

	DummyEntity* pEntitySelected;

private:
	void TrySetSelectedEntity(DummyEntity* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};