#pragma once

#include "Entity.h"

class EnemyBulletEntity : public Entity
{
public:
	EnemyBulletEntity();
	void SetTarget(Entity* target);
	void SetSpeed(float speed);
	float GetSpeed() const;
protected:
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
private:
	Entity* m_target;
	sf::Vector2f m_direction;
	float m_speed;
};
