#pragma once
#include "Entity.h"

class CoinEntity : public Entity
{
protected:
public:
	void OnUpdate() override;
	void OnCollision(Entity* other) override;
};
