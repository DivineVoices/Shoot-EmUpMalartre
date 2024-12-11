#pragma once

#include "Entity.h"

class EnemyBulletEntity : public Entity
{
public:
	EnemyBulletEntity();
	void SetTarget(Entity* target);
protected:
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
private:
	Entity* m_target;
};
