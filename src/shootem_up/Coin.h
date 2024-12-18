#pragma once
#include "Entity.h"

class Coinntity : public Entity
{
protected:
	int CoinNumber = 0;
public:
	void OnCollision(Entity* other) override;
};
