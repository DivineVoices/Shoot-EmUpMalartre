#pragma once
#include "EnemyEntity.h"

class BossEntity : public EnemyEntity
{
protected:
	void OnUpdate() override;
	void Phase1();
	void Phase2();
	void Phase3();
	void PhaseGestion();
public:
	void SetTarget(Entity* player) { mPlayer = player; }
	void BasicShoot();
	void WallShoot();
	void CanonShoot();
	void RoundShoot();
	void LaserShoot();
	BossEntity()
	{
		EnemyLife = 900;
	}

	int GetLife() const { return EnemyLife; }
private:
	Entity* mPlayer = nullptr;

	bool lanerSpawn = false;
	bool lanerHasSpaw = false;

	float timeSinceLastBasicBossShot = 0.0f;
	float timeSinceLastWallBossShot = 0.0f;
	float timeSinceLastBossCanonShot = 0.0f;
	float timeSinceLastBossRoundShot = 0.0f;
	float timeSinceLastBossLaserShot = 0.0f;

	float timer = 0.0f;
};
