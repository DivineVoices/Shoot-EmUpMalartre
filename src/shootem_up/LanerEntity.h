#pragma once
#include "EnemyEntity.h"

class LanerEntity : public EnemyEntity
{
protected:
public:
	LanerEntity()
	{
		EnemyLife = 15;
	}
	void OnUpdate() override;
	void Shoot();
};
