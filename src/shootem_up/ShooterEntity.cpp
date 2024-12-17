#include "pch.h"

#include "ShooterEntity.h"

#include "EnemyBullet.h"

#include "SampleScene.h"

#include <iostream>

void ShooterEntity::OnUpdate()
{
    GoToDirection(-10000, GetPosition().y, 60);
}

void ShooterEntity::Shoot()
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
        EnemyBulletEntity* badbullet = CreateEntity<EnemyBulletEntity>(5, sf::Color::Red);

        if (badbullet == nullptr)
        {
            std::cout << "[DEBUG] �chec de la cr�ation de la balle !" << std::endl;
            continue;
        }

        badbullet->SetPosition(shooterPosition.x, shooterPosition.y);
        badbullet->SetSpeed(250.0f);
        badbullet->SetTarget(mPlayer);
    }
    sf::Vector2f position = GetPosition();
    if (position.x > 1280 || position.x < 0 || position.y > 720 || position.y < 0) {
        Destroy();
    }
}
