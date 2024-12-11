#pragma once
#include "EnemyEntity.h"

class ShooterEntity : public EnemyEntity
{
protected:
public:
	ShooterEntity()
	{
		EnemyLife = 25;
	}
	void OnUpdate() override;
	void Shoot();
};
