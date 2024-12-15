#pragma once
#include "EnemyEntity.h"

class BossEntity : public EnemyEntity
{
protected:
	void OnUpdate() override;
	void Shoot();
public:
	BossEntity()
	{
		EnemyLife = 900;
	}
};
