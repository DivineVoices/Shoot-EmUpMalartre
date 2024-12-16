#include "pch.h"

#include "BossEntity.h"

#include "EnemyBullet.h"

#include "SampleScene.h"

#include <iostream>

void BossEntity::OnUpdate()
{

}

void BossEntity::Shoot()
{
    Scene* scene = GetScene();
    if (scene == nullptr)
    {
        std::cout << "[DEBUG] La scène est nulle, tir annulé." << std::endl;
        return;
    }

    sf::Vector2f bossPosition = GetPosition();
    std::cout << "[DEBUG] Position de l'ennemie shooter : (" << bossPosition.x << ", " << bossPosition.y << ")" << std::endl;

    const int bulletCount = 1;

    for (int i = 0; i < bulletCount; ++i)
    {
        EnemyBulletEntity* badbullet = CreateEntity<EnemyBulletEntity>(10, 10, "../../../res/ennemybullet.png", 1, 1, 1.0f);

        if (badbullet == nullptr)
        {
            std::cout << "[DEBUG] Échec de la création de la balle !" << std::endl;
            continue;
        }

        badbullet->SetPosition(bossPosition.x, bossPosition.y);
    }
}
