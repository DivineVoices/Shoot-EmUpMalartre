#include "pch.h"

#include "LanerBullet.h"

#include "SampleScene.h"

#include "Windows.h"

#include "EnemyEntity.h"

LanerBulletEntity::LanerBulletEntity()
{
    SetTag(SampleScene::Tag::ENEMYBULLET);
}

void LanerBulletEntity::OnUpdate()
{
    GoToDirection(-10000, GetPosition().y, 850);

    if (ToDestroy()) return;

    Scene* scene = GetScene();
    if (scene == nullptr) return;

    int width = scene->GetWindowWidth();

    sf::Vector2f position = GetPosition();
    if (position.x > 1280 || position.x < 0 || position.y > 720 || position.y < 0) {
        Destroy();
    }
}


void LanerBulletEntity::OnCollision(Entity* pCollidedWith)
{
    if (pCollidedWith == nullptr) return;

    if (pCollidedWith->IsTag(SampleScene::Tag::PLAYER))
    {
        EnemyEntity* player = dynamic_cast<EnemyEntity*>(pCollidedWith);
        if (player != nullptr)
        {
            player->TakeDamage(1);
        }
        Destroy();
    }
}