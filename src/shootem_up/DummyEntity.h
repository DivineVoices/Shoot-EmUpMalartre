#pragma once
#include "Entity.h"

class DummyEntity : public Entity
{
public:
	void OnCollisionCircleCircle(Entity* other) override;
	void OnCollisionRectRect(Entity* other) override;
	void OnCollisionCircleRect(Entity* other) override;
};

