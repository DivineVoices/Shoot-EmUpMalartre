#include "pch.h"

#include "Bullet.h"

#include "SampleScene.h"

#include "Windows.h"

void BulletEntity::OnUpdate()
{
    GoToDirection(10000, GetPosition().y, 850);

    if (ToDestroy()) return;

    Scene* scene = GetScene();
    if (scene == nullptr) return;

    sf::Vector2f position = GetPosition(0.f, 0.f);
    int width = scene->GetWindowWidth();

    if (position.x > 1280) {
        Destroy();
        //std::cout << "Hakai" << std::endl;
    }
}


void BulletEntity::OnCollision(Entity* pCollidedWith)
{
    if (pCollidedWith == nullptr) return;
	if (pCollidedWith->IsTag(SampleScene::Tag::ENNEMIES))
	{
		Destroy();
	}

}