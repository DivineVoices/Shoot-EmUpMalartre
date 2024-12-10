#include "pch.h"

#include "RocketBullet.h"

#include "SampleScene.h"

#include "Bullet.h"

#include "Windows.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void RocketBulletEntity::OnCollision(Entity* pCollidedWith)
{
    if (pCollidedWith == nullptr) return;

    if (pCollidedWith->IsTag(SampleScene::Tag::ENNEMIES))
    {
        Explode();
        Destroy();
    }
}

void RocketBulletEntity::Explode()
{
    Scene* scene = GetScene();
    if (scene == nullptr)
    {
        std::cout << "[DEBUG] La scène est nulle, l'explosion est annulée." << std::endl;
        return;
    }

    sf::Vector2f explosionPosition = GetPosition();
    std::cout << "[DEBUG] Position de l'explosion : (" << explosionPosition.x << ", " << explosionPosition.y << ")" << std::endl;

    const int bulletCount = 1;
    const float speed = 5.0f;

    for (int i = 0; i < bulletCount; ++i)
    {
        BulletEntity* bullet = CreateEntity<BulletEntity>(200, sf::Color::Yellow);

        if (bullet == nullptr)
        {
            std::cout << "[DEBUG] Échec de la création de la balle !" << std::endl;
            continue;
        }

        bullet->SetPosition(explosionPosition.x, explosionPosition.y);
    }
}




