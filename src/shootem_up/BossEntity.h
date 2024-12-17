#pragma once
#include "EnemyEntity.h"

class BossEntity : public EnemyEntity
{
protected:
	void OnUpdate() override;
	void Phase1();
	void Phase2();
	void Phase3();
public:
	void SetTarget(Entity* player) { mPlayer = player; }
	void BasicShoot();
	void WallShoot();
	void EventailShoot();
	BossEntity()
	{
		EnemyLife = 900;
	}
private:
	Entity* mPlayer = nullptr;
	float timeSinceLastBossShot = 0.0f;
	float timer = 0.0f;
};
