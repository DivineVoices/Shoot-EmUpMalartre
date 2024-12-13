#pragma once
#include "EnemyEntity.h"

class LanerEntity : public EnemyEntity
{
protected:
public:
	LanerEntity()
	{
		EnemyLife = 30;
	}
	void OnUpdate() override;
	void Shoot();
};
