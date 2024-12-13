#include "pch.h"

#include "PlayerEntity.h"

#include <iostream>

void PlayerEntity::OnCollision(Entity* other)
{
	PlayerLife -= 1;
	std::cout << "PlayerOnColision" << std::endl;
}

void PlayerEntity::TakeDamage(int dmg)
{
    PlayerLife -= dmg;
    std::cout << "OOOOOFFFFFFFF !!!!! Vie de l'ennemie: " << PlayerLife << std::endl;

    if (PlayerLife <= 0)
    {
        Destroy();
    }
}
