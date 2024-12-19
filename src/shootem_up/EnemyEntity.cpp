#include "pch.h"

#include "EnemyEntity.h"
#include "AudioManager.h"	

#include "SampleScene.h"

#include <iostream>

void EnemyEntity::OnCollision(Entity* other)
{
	std::cout << "EnemyEntity::OnCollision" << std::endl;
	std::cout << EnemyLife << std::endl;
}

void EnemyEntity::TakeDamage(int dmg)
{
    EnemyLife -= dmg;
    std::cout << "AHHHHHHHH !!!!! Vie de l'ennemie: " << EnemyLife << std::endl;

    if (EnemyLife <= 0)
    {
        Destroy();
    }
}
