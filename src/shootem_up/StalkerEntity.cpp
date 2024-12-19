#include "pch.h"

#include "StalkerEntity.h"

#include "SampleScene.h"

#include <iostream>

void StalkerEntity::OnUpdate()
{
    if (mPlayer != nullptr) 
    {
        sf::Vector2f playerPos = mPlayer->GetPosition();
        SetPosition(playerPos.x + 150, playerPos.y);
    }

    EnemyEntity::OnUpdate();
}
