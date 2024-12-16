#pragma once
#include "EnemyEntity.h"

class BossEntity : public EnemyEntity
{
protected:
	void OnUpdate() override;
	void Shoot();
public:
	void SetTarget(Entity* player) { mPlayer = player; }
	BossEntity()
	{
		EnemyLife = 900;
	}
private:
	Entity* mPlayer = nullptr;
};
