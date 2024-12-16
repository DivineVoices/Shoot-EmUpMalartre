#include "pch.h"

#include "HomingBullet.h"

#include "SampleScene.h"

#include "Windows.h"

#include "EnemyEntity.h"

HomingBulletEntity::HomingBulletEntity()
    : m_target(nullptr) {}

void HomingBulletEntity::SetTarget(Entity* target)
{
    m_target = target;
}

void HomingBulletEntity::OnUpdate()
{
    if (m_target == nullptr) return; 
    
    sf::Vector2f targetPosition = m_target->GetPosition();
    sf::Vector2f currentPosition = GetPosition();
    sf::Vector2f direction = targetPosition - currentPosition;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0.f)
    {
        direction /= length;
        GoToDirection(currentPosition.x + direction.x * 5, currentPosition.y + direction.y * 5, 250);
    }

    if (ToDestroy()) return;

    Scene* scene = GetScene();
    if (scene == nullptr) return;

    sf::Vector2f position = GetPosition();
    if (position.x > 1280 || position.x < 0 || position.y > 720 || position.y < 0) {
        Destroy();
    }
}

void HomingBulletEntity::OnCollision(Entity* pCollidedWith)
{
    if (pCollidedWith == nullptr) return;

    if (pCollidedWith->IsTag(SampleScene::Tag::ENNEMIES))
    {
        EnemyEntity* enemy = dynamic_cast<EnemyEntity*>(pCollidedWith);
        if (enemy != nullptr)
        {
            enemy->TakeDamage(10);
        }
        Destroy();
    }
}
