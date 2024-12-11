#pragma once

#include "EnemyEntity.h"
#include "DummyEntity.h"

class StalkerEntity : public EnemyEntity
{
public:
    StalkerEntity()
    {
        EnemyLife = 50;
    }
	void OnUpdate() override;

    DummyEntity* mPlayer;
};