#pragma once
#include "EntityLightEngine.h"

class DummyEntity : public Entity
{
public:
	void OnCollision(Entity* other) override;
};

