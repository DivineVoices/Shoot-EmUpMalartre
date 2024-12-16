#include "pch.h"

#include "TestScene.h"

#include "DummyEntity.h"

#include "Debug.h"

void TestScene::OnInitialize()
{
	pEntity1 = CreateEntity<DummyEntity>(30, 30, "../../../res/player.png", 1, 1, 1.0f);
	pEntity1->SetPosition(100, 100);
	pEntity1->SetCollisionType(Entity::CollisionType::AABB);

	pEntity2 = CreateEntity<DummyEntity>(30, 30, "../../../res/boss.png", 1, 1, 1.0f);
	pEntity2->SetPosition(500, 500);
	pEntity2->SetCollisionType(Entity::CollisionType::AABB);

	pEntitySelected = nullptr;
}

void TestScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		TrySetSelectedEntity(pEntity1, event.mouseButton.x, event.mouseButton.y);
		TrySetSelectedEntity(pEntity2, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr)
		{
			pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
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