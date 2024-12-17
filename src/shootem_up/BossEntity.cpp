#include "pch.h"

#include "BossEntity.h"

#include "EnemyBullet.h"

#include "LanerBullet.h"

#include "KamikazeEntity.h"

#include "LanerEntity.h"

#include "SampleScene.h"

#include <iostream>

void BossEntity::OnUpdate()
{
    PhaseGestion();
    if (EnemyLife >= 601) Phase1();
    else if (EnemyLife <= 600 && EnemyLife >= 301) Phase2();
    else if (EnemyLife <= 300) Phase3();
}

void BossEntity::Phase1()
{
    float bossBasicShootCooldown = 0.5f;
    float bossWallShootCooldown = 0.7f;

    timeSinceLastBasicBossShot += GameManager::Get()->GetDeltaTime();
    timeSinceLastWallBossShot += GameManager::Get()->GetDeltaTime();

    if (timeSinceLastBasicBossShot >= bossBasicShootCooldown)
    {
        BasicShoot();
        timeSinceLastBasicBossShot = 0.0f;
    }

    if (timeSinceLastWallBossShot >= bossWallShootCooldown)
    {
        WallShoot();
        timeSinceLastWallBossShot = 0.0f;
    }
}

void BossEntity::Phase2()
{
    Scene* scene = GetScene();

    if (scene == nullptr)
    {
        return;
    }
    LanerEntity* FinalLaner1 = nullptr;
    LanerEntity* FinalLaner2 = nullptr;

    if (lanerSpawn) {
        FinalLaner1 = CreateEntity<LanerEntity>(60, sf::Color::Red);
        if (FinalLaner1) {
            FinalLaner1->SetPosition(700, 144);
        }

        FinalLaner2 = CreateEntity<LanerEntity>(60, sf::Color::Red);
        if (FinalLaner2) {
            FinalLaner2->SetPosition(700, 576);
        }

        lanerSpawn = false;
        lanerHasSpaw = true;
    }

    if (FinalLaner1) {
        FinalLaner1->Shoot();
    }

    if (FinalLaner2) {
        FinalLaner2->Shoot();
    }

    float bossCanonShootCooldown = 0.5f;

    timeSinceLastBossCanonShot += GameManager::Get()->GetDeltaTime();

    if (timeSinceLastBossCanonShot >= bossCanonShootCooldown)
    {
        CanonShoot();
        timeSinceLastBossCanonShot = 0.0f;
    }
}

void BossEntity::Phase3()
{
    float bossRoundLaserCooldown = 0.0f;
    float bossRoundShootCooldown = 1.0f;

    timeSinceLastBossRoundShot += GameManager::Get()->GetDeltaTime();
    timeSinceLastBossLaserShot += GameManager::Get()->GetDeltaTime();

    if (timeSinceLastBossRoundShot >= bossRoundShootCooldown)
    {
        RoundShoot();
        timeSinceLastBossRoundShot = 0.0f;
    }

    if (timeSinceLastBossRoundShot >= bossRoundLaserCooldown)
    {
        LaserShoot();
        timeSinceLastBossLaserShot = 0.0f;
    }
}

void BossEntity::PhaseGestion()
{
    if (EnemyLife <= 600 && !lanerHasSpaw) lanerSpawn = true;
}

void BossEntity::BasicShoot()
{
    Scene* scene = GetScene();
    if (scene == nullptr)
    {
        return;
    }

    sf::Vector2f bossPosition = GetPosition();

    const int bulletCount = 1;

    for (int i = 0; i < bulletCount; ++i)
    {
        EnemyBulletEntity* badbullet = CreateEntity<EnemyBulletEntity>(13, sf::Color::Red);

        if (badbullet == nullptr)
        {
            continue;
        }

        badbullet->SetPosition(bossPosition.x, bossPosition.y);
        badbullet->SetSpeed(250.0f);
        badbullet->SetTarget(mPlayer);
    }
}

void BossEntity::WallShoot()
{
    Scene* scene = GetScene();
    if (scene == nullptr)
    {
        return;
    }

    sf::Vector2f bossPosition = GetPosition();

    const int bulletCount = 5;
    const float spacing = 60.0f;

    for (int i = 0; i < bulletCount; ++i)
    {
        EnemyBulletEntity* bullet = CreateEntity<EnemyBulletEntity>(15, sf::Color::Red);

        if (bullet == nullptr)
        {
            continue;
        }

        float posInBoss = (i - bulletCount / 2) * spacing;
        bullet->SetPosition(bossPosition.x, bossPosition.y + posInBoss);

        sf::Vector2f bulletTarget = sf::Vector2f(bossPosition.x + posInBoss +20, 720.0f);

        bullet->SetTarget(mPlayer);
        bullet->SetSpeed(300.0f);
    }
}

void BossEntity::CanonShoot()
{
    Scene* scene = GetScene();
    if (scene == nullptr)
    {
        return;
    }

    sf::Vector2f bossPosition = GetPosition();

    const int bulletCount = 1;

    for (int i = 0; i < bulletCount; ++i)
    {
        EnemyBulletEntity* badbullet = CreateEntity<EnemyBulletEntity>(20, sf::Color::Red);

        if (badbullet == nullptr)
        {
            continue;
        }
        badbullet->SetPosition(bossPosition.x, bossPosition.y);
        badbullet->SetSpeed(1000.0f);
        badbullet->SetTarget(mPlayer);
    }
}

void BossEntity::RoundShoot()
{
    Scene* scene = GetScene();
    if (scene == nullptr)
    {
        return;
    }

    sf::Vector2f bossPosition = GetPosition();

    const int bulletCount = 10;
    const float radius = 100.0f;
    const float angleStep = 360.0f / bulletCount;

    for (int i = 0; i < bulletCount; ++i)
    {
        EnemyBulletEntity* bullet = CreateEntity<EnemyBulletEntity>(15, sf::Color::Red);

        if (bullet == nullptr)
        {
            continue;
        }

        float angle = i * angleStep;
        float xOffset = radius * cos(angle * 3.14159f / 180.0f);
        float yOffset = radius * sin(angle * 3.14159f / 180.0f);

        bullet->SetPosition(bossPosition.x + xOffset, bossPosition.y + yOffset);
        bullet->SetSpeed(300);

        bullet->SetTarget(mPlayer);
    }
}

void BossEntity::LaserShoot()
{
    Scene* scene = GetScene();
    if (scene == nullptr)
    {
        return;
    }

    sf::Vector2f bossPosition = GetPosition();

    const int bulletCount = 1;

    for (int i = 0; i < bulletCount; ++i)
    {
        LanerBulletEntity* badbullet = CreateEntity<LanerBulletEntity>(100, sf::Color::Red);

        if (badbullet == nullptr)
        {
            continue;
        }

        badbullet->SetPosition(bossPosition.x, bossPosition.y);
    }
}
