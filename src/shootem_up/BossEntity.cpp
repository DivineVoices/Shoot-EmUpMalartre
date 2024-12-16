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

void BossEntity::EventailShoot()
{
    Scene* scene = GetScene();
    if (scene == nullptr)
    {
        std::cout << "[DEBUG] La scène est nulle, tir annulé." << std::endl;
        return;
    }

    sf::Vector2f bossPosition = GetPosition();
    sf::Vector2f playerPosition = mPlayer->GetPosition();  // Récupérer la position du joueur
    std::cout << "[DEBUG] Position du joueur : (" << playerPosition.x << ", " << playerPosition.y << ")" << std::endl;

    const int bulletCount = 10; // Nombre de projectiles
    const float spreadAngle = 45.f; // Angle de dispersion (en degrés)
    const float bulletSpeed = 5.f;  // Vitesse des projectiles

    // Calculer l'angle entre chaque projectile
    float angleStep = spreadAngle / (bulletCount - 1); // Espacement entre les projectiles

    for (int i = 0; i < bulletCount; ++i)
    {
        // Calculer l'angle de dispersion pour ce projectile
        float angle = -spreadAngle / 2.f + i * angleStep;

        // Convertir l'angle en radians
        float angleRad = angle * 3.14159f / 180.f;

        // Calculer la direction vers le joueur
        sf::Vector2f direction = playerPosition - bossPosition;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0.f)
        {
            direction /= length; // Normalisation pour obtenir une direction unitaire
        }

        // Appliquer la dispersion en ajustant la direction
        sf::Vector2f dispersedDirection(
            direction.x * cos(angleRad) - direction.y * sin(angleRad),
            direction.x * sin(angleRad) + direction.y * cos(angleRad)
        );

        // Créer un nouveau projectile
        EnemyBulletEntity* badbullet = CreateEntity<EnemyBulletEntity>(10, sf::Color::Red);

        if (badbullet == nullptr)
        {
            std::cout << "[DEBUG] Échec de la création de la balle !" << std::endl;
            continue;
        }

        badbullet->SetPosition(bossPosition.x, bossPosition.y);
        badbullet->GoToDirection(bossPosition.x + dispersedDirection.x * bulletSpeed, bossPosition.y + dispersedDirection.y * bulletSpeed, bulletSpeed);
    }
}
