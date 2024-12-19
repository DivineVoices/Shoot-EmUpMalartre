#pragma once
#include "Entity.h"

class PlayerEntity : public Entity
{
	int PlayerLife = 3000;
	int CoinNumber = 0;
public:
	void OnCollision(Entity* other) override;
	void OnUpdate() override;
	virtual void TakeDamage(int dmg);
	int GetLife() const { return PlayerLife; }
	int GetCoinNumber() const { return CoinNumber; }
	void SetLife(int life) { PlayerLife = life; }
};

