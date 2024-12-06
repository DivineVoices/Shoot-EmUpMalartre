#pragma once

#include "Entity.h"

class HomingBulletEntity : public Entity
{
public:
    HomingBulletEntity();
    void SetTarget(Entity* target);
protected:
    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
private:
    Entity* m_target; 
};
