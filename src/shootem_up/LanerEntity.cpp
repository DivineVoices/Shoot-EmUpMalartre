#include "pch.h"

#include "LanerEntity.h"

#include "LanerBullet.h"

#include "SampleScene.h"

#include <iostream>

void LanerEntity::OnUpdate()
{

}

void LanerEntity::Shoot()
{
    Scene* scene = GetScene();
    if (scene == nullptr)
    {
        std::cout << "[DEBUG] La sc�ne est nulle, tir annul�." << std::endl;
        return;
    }

    sf::Vector2f shooterPosition = GetPosition();
    std::cout << "[DEBUG] Position de l'ennemie shooter : (" << shooterPosition.x << ", " << shooterPosition.y << ")" << std::endl;

    const int bulletCount = 1;

    for (int i = 0; i < bulletCount; ++i)
    {
        LanerBulletEntity* badbullet = CreateEntity<LanerBulletEntity>(10, sf::Color::Red);

        if (badbullet == nullptr)
        {
            std::cout << "[DEBUG] �chec de la cr�ation de la balle !" << std::endl;
            continue;
        }

        badbullet->SetPosition(shooterPosition.x, shooterPosition.y);
    }

    sf::Vector2f position = GetPosition();
    if (position.x > 1280 || position.x < 0 || position.y > 720 || position.y < 0) {
        Destroy();
    }
}
