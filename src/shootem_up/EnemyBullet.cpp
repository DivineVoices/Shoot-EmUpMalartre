#include "pch.h"

#include "EnemyBullet.h"

#include "SampleScene.h"

#include "Windows.h"

#include "EnemyEntity.h"

EnemyBulletEntity::EnemyBulletEntity()
    : m_target(nullptr)
{
    SetTag(SampleScene::Tag::ENEMYBULLET);
}

void EnemyBulletEntity::SetTarget(Entity* target)
{
    m_target = target;
}

void EnemyBulletEntity::OnUpdate()
{
    GoToDirection(-10000, GetPosition().y, 850);

    if (ToDestroy()) return;

    Scene* scene = GetScene();
    if (scene == nullptr) return;

    sf::Vector2f position = GetPosition(0.f, 0.f);
    int width = scene->GetWindowWidth();

    if (position.x > 1280) {
        Destroy();
    }
}


void EnemyBulletEntity::OnCollision(Entity* pCollidedWith)
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