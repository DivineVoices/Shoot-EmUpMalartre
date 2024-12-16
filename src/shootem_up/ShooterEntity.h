#pragma once
#include "EnemyEntity.h"

class ShooterEntity : public EnemyEntity
{
protected:
public:
	ShooterEntity()
	{
		EnemyLife = 10;
	}
	void OnUpdate() override;
	void Shoot();
};
