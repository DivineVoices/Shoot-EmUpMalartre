#pragma once

#include "EnemyEntity.h"
#include "PlayerEntity.h"

class StalkerEntity : public EnemyEntity
{
public:
    StalkerEntity()
    {
        EnemyLife = 8;
    }
	void OnUpdate() override;

    PlayerEntity* mPlayer;
};