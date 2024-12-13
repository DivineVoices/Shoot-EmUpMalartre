#pragma once

#include "Scene.h"

#include "iostream"

#include <vector>

class DummyEntity;
class EnemyEntity;
class StalkerEntity;
class KamikazeEntity;
class ShooterEntity;
class LanerEntity;

class EnemyBulletEntity;
class LanerBulletEntity;

class BulletEntity;
class HomingBulletEntity;
class RocketBulletEntity;

struct AABB
{
	int xMin;
	int yMin;
	int xMax;
	int yMax;
};

class SampleScene : public Scene
{
	std::vector<DummyEntity*> pDummy;
	std::vector<EnemyEntity*> pEnemy;
	std::vector<StalkerEntity*> pStalker;
	std::vector<KamikazeEntity*> pKamikaze;
	std::vector<ShooterEntity*> pShooter;
	std::vector<LanerEntity*> pLaner;

	std::vector<EnemyBulletEntity*> pEnemyProjectiles;
	std::vector<LanerBulletEntity*> pLanerProjectiles;

	std::vector<BulletEntity*> pProjectiles;
	std::vector<HomingBulletEntity*> pHoming;
	std::vector<RocketBulletEntity*> pRocket;

	DummyEntity* pPlayer;

	DummyEntity* pEntitySelected;

private:
	void TrySetSelectedEntity(int x, int y);

	int x;
	int y;

	int pPx;
	int pPy;

	int speed;
	sf::Vector2f direction;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

	enum Tag
	{
		ENNEMIES,
		PLAYER,
		BULLET,
		ENEMYBULLET
	};

	AABB mAreas[5];

};


