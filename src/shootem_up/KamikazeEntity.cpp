#include "pch.h"

#include "KamikazeEntity.h"

#include "SampleScene.h"

#include <iostream>

void KamikazeEntity::OnUpdate()
{
    if (mPlayer == nullptr) return;

    sf::Vector2f targetPosition = mPlayer->GetPosition();
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

    sf::Vector2f position = GetPosition(0.f, 0.f);
    int width = scene->GetWindowWidth();
}

void KamikazeEntity::SetTarget(Entity* target)
{
    mPlayer = target;
}
