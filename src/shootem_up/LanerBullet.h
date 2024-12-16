#pragma once

#include "Entity.h"

class LanerBulletEntity : public Entity
{
public:
	LanerBulletEntity();
protected:
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
};
