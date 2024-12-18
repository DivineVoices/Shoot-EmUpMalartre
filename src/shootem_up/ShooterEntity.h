#pragma once
#include "EnemyEntity.h"

class ShooterEntity : public EnemyEntity
{
protected:
public:
	void SetTarget(Entity* player) { mPlayer = player; }
	ShooterEntity()
	{
		EnemyLife = 10;
	}
	void OnUpdate() override;
	void Shoot();
	Entity* mPlayer = nullptr;
private:
	float timeSinceLastEnemyShot = 0.0f;
};
