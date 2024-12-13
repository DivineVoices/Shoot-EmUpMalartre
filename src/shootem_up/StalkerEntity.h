#pragma once

#include "EnemyEntity.h"
#include "DummyEntity.h"

class StalkerEntity : public EnemyEntity
{
public:
    StalkerEntity()
    {
        EnemyLife = 8;
    }
	void OnUpdate() override;

    DummyEntity* mPlayer;
};