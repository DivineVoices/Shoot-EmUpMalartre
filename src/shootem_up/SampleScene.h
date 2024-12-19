#pragma once

#include "Scene.h"

#include "iostream"

#include <vector>

#include <fstream>

#include <string>


class DummyEntity;
class EnemyEntity;
class StalkerEntity;
class KamikazeEntity;
class ShooterEntity;
class LanerEntity;
class PlayerEntity;
class BossEntity;

class CoinEntity;

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
	std::vector<Entity*> pAllEnemies;

	std::vector<DummyEntity*> pDummy;
	std::vector<EnemyEntity*> pEnemy;
	std::vector<StalkerEntity*> pStalker;
	std::vector<KamikazeEntity*> pKamikaze;
	std::vector<ShooterEntity*> pShooter;
	std::vector<LanerEntity*> pLaner;
	std::vector<BossEntity*> pBoss;

	std::vector<CoinEntity*> pCoin;

	std::vector<EnemyBulletEntity*> pEnemyProjectiles;
	std::vector<LanerBulletEntity*> pLanerProjectiles;

	std::vector<BulletEntity*> pProjectiles;
	std::vector<HomingBulletEntity*> pHoming;
	std::vector<RocketBulletEntity*> pRocket;

	PlayerEntity* pPlayer;

	DummyEntity* pEntitySelected;

private:
	void TrySetSelectedEntity(int x, int y);

	int x;
	int y;

	int pPx;
	int pPy;

	float Timer;
	std::vector<std::string> waves;
	size_t currentWaveIndex = 0;

	int speed;
	//int coinNumber;

	bool gameOver = false;

	float timeSinceLastShot = 0.0f;

	sf::Vector2f direction;

	int BackSpeed = 2;
	int PlanetSpeed = 32;
	int CitySpeed2 = 64;
	int CitySpeed = 128;
	int RoadSpeed = 256;
	int BackY = 0;
	int PlanetY = 150;
	int CityY = 152;
	int RoadY = 550;
	int GoalX = -2500;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void ProcessWave(const std::string& wave);
	void RestartGame();

	enum Tag
	{
		ENNEMIES,
		PLAYER,
		BULLET,
		ENEMYBULLET,
		COIN
	};

	AABB mAreas[5];

};


