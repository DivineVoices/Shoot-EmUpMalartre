#pragma once
#include "Entity.h"

class PlayerEntity : public Entity
{
	int PlayerLife = 3000;
public:
	void OnCollision(Entity* other) override;
	void OnUpdate() override;
	virtual void TakeDamage(int dmg);
};

