#pragma once

#include "EnemyEntity.h"
#include "DummyEntity.h"

class KamikazeEntity : public EnemyEntity
{
public:
    KamikazeEntity()
    {
        EnemyLife = 11;
    }
    void OnUpdate() override;
    void SetTarget(Entity* target);
    Entity* mPlayer;
};