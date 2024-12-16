#include "pch.h"

#include "PlayerEntity.h"

#include "SampleScene.h"

#include <iostream>

void PlayerEntity::OnCollision(Entity* other)
{
    if (other->IsTag(SampleScene::Tag::ENNEMIES) || other->IsTag(SampleScene::Tag::ENEMYBULLET))
    {
        PlayerLife -= 1;
        std::cout << "PlayerOnColision" << std::endl;
        std::cout << "OOOOOFFFFFFFF !!!!! Vie du joueur: " << PlayerLife << std::endl;
    }
}

void PlayerEntity::OnUpdate()
{
    if (PlayerLife <= 0)
    {
        Destroy();
    }

}

void PlayerEntity::TakeDamage(int dmg)
{
    PlayerLife -= dmg;
    std::cout << "OOOOOFFFFFFFF !!!!! Vie du joueur: " << PlayerLife << std::endl;
}
