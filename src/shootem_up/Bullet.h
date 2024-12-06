#pragma once

#include "Entity.h"

class BulletEntity : public Entity
{
public:

protected:
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
};
