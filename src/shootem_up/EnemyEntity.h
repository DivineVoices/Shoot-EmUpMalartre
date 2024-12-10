#pragma once
#include "Entity.h"

class EnemyEntity : public Entity
{
protected:
	int EnemyLife = 20;
public:
	void OnCollision(Entity* other) override;
	virtual void TakeDamage(int dmg);
};
