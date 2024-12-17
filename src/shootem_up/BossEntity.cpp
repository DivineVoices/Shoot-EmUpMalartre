#include "pch.h"

#include "BossEntity.h"

#include "EnemyBullet.h"

#include "SampleScene.h"

#include <iostream>

void BossEntity::OnUpdate()
{
    Phase1();
}

void BossEntity::Phase1()
{
    float bossShootCooldown = 0.5f;

    timeSinceLastBossShot += GameManager::Get()->GetDeltaTime();

    if (timeSinceLastBossShot >= bossShootCooldown)
    {
        EventailShoot();
        timeSinceLastBossShot = 0.0f;
    }
}

void BossEntity::Phase2()
{
}

void BossEntity::Phase3()
{
}

void BossEntity::BasicShoot()
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
        EnemyBulletEntity* badbullet = CreateEntity<EnemyBulletEntity>(10, sf::Color::Red);

        if (badbullet == nullptr)
        {
            std::cout << "[DEBUG] Échec de la création de la balle !" << std::endl;
            continue;
        }

        badbullet->SetPosition(bossPosition.x, bossPosition.y);
        badbullet->SetTarget(mPlayer);
    }
}

void BossEntity::WallShoot()
{
    Scene* scene = GetScene();
    if (scene == nullptr)
    {
        std::cout << "[DEBUG] La scène est nulle, tir annulé." << std::endl;
        return;
    }

    sf::Vector2f bossPosition = GetPosition();
    std::cout << "[DEBUG] Position du Boss pour EventailShoot : (" << bossPosition.x << ", " << bossPosition.y << ")" << std::endl;

    const int bulletCount = 5;
    const float spacing = 60.0f;

    for (int i = 0; i < bulletCount; ++i)
    {
        EnemyBulletEntity* bullet = CreateEntity<EnemyBulletEntity>(10, sf::Color::Red);

        if (bullet == nullptr)
        {
            std::cout << "[DEBUG] Échec de la création d'une balle !" << std::endl;
            continue;
        }

        float posInBoss = (i - bulletCount / 2) * spacing;
        bullet->SetPosition(bossPosition.x, bossPosition.y + posInBoss);

        sf::Vector2f bulletTarget = sf::Vector2f(bossPosition.x + posInBoss +20, 720.0f);

        bullet->SetTarget(mPlayer);
    }
}

void BossEntity::EventailShoot()
{
}


