#include "pch.h"

#include "SampleScene.h"

#include "DummyEntity.h"

#include "Bullet.h"

#include "HomingBullet.h"

#include "RocketBullet.h"

#include "Debug.h"

void SampleScene::OnInitialize()
{
	pDummy.push_back(CreateEntity<DummyEntity>(100, sf::Color::Red));
	pDummy.back()->SetPosition(1000, 100);
	pDummy.back()->SetTag(Tag::ENNEMIES);

	pDummy.push_back(CreateEntity<DummyEntity>(100, sf::Color::Red));
	pDummy.back()->SetPosition(1000, 300);
	pDummy.back()->SetTag(Tag::ENNEMIES);

	pPlayer = CreateEntity<DummyEntity>(25, sf::Color::White);
	pPlayer->SetPosition(800, 350);

	x = pPlayer->GetPosition().x;
	y = pPlayer->GetPosition().y;

	speed = 200;

	pEntitySelected = nullptr;

	int yMin = 720;
	int yMax = 576;
	for (int i = 0; i < 5; i++) {
		mAreas[i] = { 0, yMin, 1280, yMax };
		yMin -= 144;
		yMax -= 144;
	}
}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Button::Left)
		{
			if (pEntitySelected != nullptr) 
			{
				pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
			}
		}
		if (event.mouseButton.button == sf::Mouse::Button::Right)
		{
			TrySetSelectedEntity(event.mouseButton.x, event.mouseButton.y);
		}
	}

	if (event.type == sf::Event::KeyPressed) 
	{
		// Mouvement
		if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
			direction.x = 1;
		}
		else if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Left) {
			direction.x = -1;
		}
		else if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up) {
			direction.y = -1;
		}
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
			direction.y = 1;
		}

		//Missiles spéciaux
		if (event.key.code == sf::Keyboard::E) {
			pPy -= 25;
			for (int i = 0; i < 4; i++) {
				pHoming.push_back(CreateEntity<HomingBulletEntity>(10, sf::Color::Blue));
				for (auto& enemy : pDummy) {
					if (enemy->IsTag(SampleScene::Tag::ENNEMIES)) {
						pHoming.back()->SetTarget(enemy);
						break;
					}
				}
				pHoming.back()->SetPosition(pPx, pPy);
				pPy += 15;
			}	
		}

		if (event.key.code == sf::Keyboard::R) {
			pRocket.push_back(CreateEntity<RocketBulletEntity>(10, sf::Color::Green));
			pRocket.back()->SetPosition(pPx, pPy);
		}
	}

	if (event.type == sf::Event::KeyReleased) 
	{
		if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right ||
			event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Left) {
			direction.x = 0;
		}
		if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up ||
			event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
			direction.y = 0;
		}
	}

}

void SampleScene::TrySetSelectedEntity(int x, int y)
{
	for (auto& enemy : pDummy) {
		if (enemy->IsInside(x, y)) {
			pEntitySelected = enemy;
			return; // Sort de la boucle dès qu'une entité est sélectionnée
		}
	}
	pEntitySelected = nullptr;
}

void SampleScene::OnUpdate()
{
	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}

	//Lanes pour le débug
	for (int i = 0; i < 5; i++)
	{
		const AABB& aabb = mAreas[i];

		Debug::DrawRectangle(aabb.xMin, aabb.yMin, aabb.xMax - aabb.xMin, aabb.yMax - aabb.yMin, sf::Color::White);
	}

	//Projectile
	//std::cout << "Projectiles remaining: " << pProjectiles.size() << std::endl;

	for (auto it = pProjectiles.begin(); it != pProjectiles.end(); ) {
		BulletEntity* pBullet = *it;
		if (pBullet->GetPosition().x > 1280) {
			//std::cout << "Deleting Bullet: " << pBullet << std::endl;
			pBullet->Destroy();
			it = pProjectiles.erase(it);
		}
		else {
			++it;
		}
	}

	//Homing
	for (size_t i = 0; i < pHoming.size(); ++i)
	{
		for (auto& enemy : pDummy)
		{
			if (enemy->IsTag(SampleScene::Tag::ENNEMIES))
			{
				pHoming[i]->SetTarget(enemy);
				break;
			}
		}
	}

	//Creation des projectiles
	pPx = pPlayer->GetPosition().x + 35;
	pPy = pPlayer->GetPosition().y;

	/*pProjectiles.push_back(CreateEntity<BulletEntity>(5, sf::Color::Yellow));
	pProjectiles.back()->SetPosition(pPx, pPy);*/

	float dt = GameManager::Get()->GetDeltaTime();
	sf::Vector2f velocity = direction * (speed * dt);

	x += velocity.x;
	y += velocity.y;

	pPlayer->SetPosition(x, y);
}