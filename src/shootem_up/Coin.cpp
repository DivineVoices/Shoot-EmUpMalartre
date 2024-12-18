#include "pch.h"

#include "Coin.h"

#include "PlayerEntity.h"

#include "SampleScene.h"

#include <iostream>

void CoinEntity::OnUpdate()
{
    GoToDirection(-10000, GetPosition().y, 60);
}

void CoinEntity::OnCollision(Entity* other)
{
    if (other == nullptr) return;

    if (other->IsTag(SampleScene::Tag::PLAYER))
    {
        std::cout << "Collision avec le joueur détectée !" << std::endl;

        PlayerEntity* player = dynamic_cast<PlayerEntity*>(other);
        if (player != nullptr)
        {
            CoinNumber += 1;
            Destroy();
        }
    }
}
