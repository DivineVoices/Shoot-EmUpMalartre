#pragma once

#include "Entity.h"

class BulletEntity : public Entity
{
public:
	BulletEntity();
protected:
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
};
