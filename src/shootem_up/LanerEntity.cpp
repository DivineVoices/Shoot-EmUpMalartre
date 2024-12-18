#include "pch.h"

#include "LanerEntity.h"

#include "LanerBullet.h"

#include "SampleScene.h"

#include <iostream>

void LanerEntity::OnUpdate()
{
    float lanerShootCooldown = 6;
    timeSinceLastLanerShot += GameManager::Get()->GetDeltaTime();
    if (timeSinceLastLanerShot >= lanerShootCooldown)
    {
        Shoot();
    }
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
        LanerBulletEntity* badbullet = CreateEntity<LanerBulletEntity>(10, 10, "../../../res/lanerbullet.png", 1, 1, 1.0f);

        if (badbullet == nullptr)
        {
            std::cout << "[DEBUG] Échec de la création de la balle !" << std::endl;
            continue;
        }

        badbullet->SetPosition(shooterPosition.x, shooterPosition.y);
    }

    sf::Vector2f position = GetPosition();
    if (position.x > 1280 || position.x < 0 || position.y > 720 || position.y < 0) {
        Destroy();
    }
}
