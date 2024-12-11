#pragma once

#include "EnemyEntity.h"
#include "DummyEntity.h"

class StalkerEntity : public EnemyEntity
{
public:
	void OnUpdate() override;

    StalkerEntity()
    {
        EnemyLife = 50;
    }
    DummyEntity* mPlayer;
};