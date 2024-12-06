#pragma once

#include "Scene.h"

#include "iostream"

#include <vector>

class DummyEntity;

class BulletEntity;

class HomingBulletEntity;

struct AABB
{
	int xMin;
	int yMin;
	int xMax;
	int yMax;
};

class SampleScene : public Scene
{
	DummyEntity* pEntity1;
	std::vector<BulletEntity*> pProjectiles;
	std::vector<HomingBulletEntity*> pHoming;
	DummyEntity* pPlayer;

	DummyEntity* pEntitySelected;

private:
	void TrySetSelectedEntity(DummyEntity* pEntity, int x, int y);

	int x;
	int y;
	int speed;
	sf::Vector2f direction;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

	enum Tag
	{
		ENNEMIES,
		BOSS,
		PLAYER,
		BULLET
	};

	AABB mAreas[0];
};


