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
        std::cout << "[DEBUG] La scène est nulle, tir annulé." << std::endl;
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
            std::cout << "[DEBUG] Échec de la création de la balle !" << std::endl;
            continue;
        }

        badbullet->SetPosition(shooterPosition.x, shooterPosition.y);
    }
}
