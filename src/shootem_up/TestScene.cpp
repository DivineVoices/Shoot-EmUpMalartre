#include "pch.h"

#include "TestScene.h"

#include "DummyEntity.h"

#include "Debug.h"

void TestScene::OnInitialize()
{
	pEntity1 = CreateEntity<DummyEntity>(70, 70, "../../../res/player.png", 1, 1, 1.0f);
	pEntity1->SetPosition(100, 100);
	pEntity1->SetCollisionType(Entity::CollisionType::Circle);

	pEntity2 = CreateEntity<DummyEntity>(70, 70, "../../../res/boss.png", 1, 1, 1.0f);
	pEntity2->SetPosition(500, 500);
	pEntity2->SetCollisionType(Entity::CollisionType::AABB);

	pEntity3 = CreateEntity<DummyEntity>(70, 70, "../../../res/spritesheet.png", 4, 4, 1.0f);
	pEntity3->SetPosition(700, 700);
	pEntity3->SetCollisionType(Entity::CollisionType::AABB);

	pEntitySelected = nullptr;
}

void TestScene::OnEvent(const sf::Event& event)
{
	sf::Vector2f dir(0.f, 0.f);
	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		TrySetSelectedEntity(pEntity1, event.mouseButton.x, event.mouseButton.y);
		TrySetSelectedEntity(pEntity2, event.mouseButton.x, event.mouseButton.y);
		TrySetSelectedEntity(pEntity3, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr)
		{
			pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
	}

	if (event.type == sf::Event::KeyPressed)
	{


		// Mouvement
		if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
			dir.x = 1;
		}
		if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Left) {
			dir.x = -1;
		}
		if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up) {
			dir.y = -1;
		}
		if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
			dir.y = 1;
		}
		pEntity1->SetDirection(dir.x, dir.y, 200);
	}

	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right ||
			event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Left) {
			pEntity1->SetDirection(0, 0, 0);
		}
		if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up ||
			event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
			pEntity1->SetDirection(0, 0, 0);
		}
	}
}

void TestScene::TrySetSelectedEntity(DummyEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void TestScene::OnUpdate()
{
	if (pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
}