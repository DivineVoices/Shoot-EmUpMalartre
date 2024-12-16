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
private:
	Entity* mPlayer = nullptr;
};
