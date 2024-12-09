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

    if (pCollidedWith->IsTag(SampleScene::Tag::ENNEMIES) || pCollidedWith->IsTag(SampleScene::Tag::BOSS))
    {
        Explode();
        //Destroy();
    }
}

void RocketBulletEntity::Explode()
{
    Scene* scene = GetScene();
    if (scene == nullptr)
    {
        std::cout << "[DEBUG] La sc�ne est nulle, l'explosion est annul�e." << std::endl;
        return;
    }

    sf::Vector2f explosionPosition = GetPosition();
    std::cout << "[DEBUG] Position de l'explosion : (" << explosionPosition.x << ", " << explosionPosition.y << ")" << std::endl;

    const int bulletCount = 8;
    const float speed = 5.0f;

    for (int i = 0; i < bulletCount; ++i)
    {
        float angleDegrees = i * (360.0f / bulletCount);
        float angleRadians = angleDegrees * (M_PI / 180.0f);

        // Utiliser des valeurs pr�calcul�es pour �viter des valeurs num�riques impr�cises
        float cosVal = std::cos(angleRadians);
        float sinVal = std::sin(angleRadians);

        // Affichage pr�cis pour le d�bogage
        if (std::abs(cosVal) < 1e-6) cosVal = 0; // Ajustement num�rique pour �viter des valeurs trop petites
        if (std::abs(sinVal) < 1e-6) sinVal = 0;

        sf::Vector2f velocity = { cosVal * speed, sinVal * speed };

        BulletEntity* bullet = CreateEntity<BulletEntity>(5, sf::Color::Yellow);

        if (bullet == nullptr)
        {
            std::cout << "[DEBUG] �chec de la cr�ation de la balle !" << std::endl;
            continue;
        }

        bullet->SetPosition(explosionPosition.x, explosionPosition.y);
        std::cout << "[DEBUG] V�locit� appliqu�e apr�s normalisation : (" << velocity.x << ", " << velocity.y << ")" << std::endl;

        bullet->SetDirection(velocity.x, velocity.y, speed);
    }
}




