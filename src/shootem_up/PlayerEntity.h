#pragma once
#include "Entity.h"

class PlayerEntity : public Entity
{
	int PlayerLife = 3;
public:
	void OnCollision(Entity* other) override;
	virtual void TakeDamage(int dmg);
};

