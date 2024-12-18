#pragma once
#include "Entity.h"

class CoinEntity : public Entity
{
protected:
	int CoinNumber = 0;
public:
	void OnUpdate() override;
	void OnCollision(Entity* other) override;
	int GetCoinNumber() const { return CoinNumber; }
};
