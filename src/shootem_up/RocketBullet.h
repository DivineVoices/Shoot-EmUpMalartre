#pragma once

#include "Bullet.h"

class RocketBulletEntity : public BulletEntity
{
public:

protected:
	void OnCollision(Entity* pCollidedWith) override;
private:
	void Explode();
};
