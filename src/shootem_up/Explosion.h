#pragma once

#include "Entity.h"

class ExplosiontEntity : public Entity
{
public:
	ExplosiontEntity();
protected:
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
};
