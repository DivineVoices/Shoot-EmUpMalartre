#include "pch.h"

#include "Enemy.h"
#include "SampleScene.h"
#include <iostream>

EnemyEntity::EnemyEntity(float radius, const sf::Color& color) : Entity(radius, color)
{
    SetTag(SampleScene::Tag::ENEMY);
    SetDirection(-1, 0, 50);
}

void EnemyEntity::OnCollision(Entity* pCollidedWith)
{
    if (pCollidedWith->IsTag(SampleScene::Tag::BULLET))
    {
        Destroy();
    }

    Scene* scene = GetScene();
    if (scene == nullptr) return;

    sf::Vector2f position = GetPosition(0.f, 0.f);
    int width = scene->GetWindowWidth();

    if (position.x < 0) {
        Destroy();
    }
}

void EnemyEntity::OnDestroy()
{
    _ASSERT(mLane != -1);

    SampleScene* pScene = GetScene<SampleScene>();
    pScene->OnDestroyEnemy(mLane);
}
