#include "pch.h"

#include "SampleScene.h"

#include "DummyEntity.h"

#include "Debug.h"

#include "AssetManager.h"

void SampleScene::OnInitialize()
{
	AssetManager assetManager;

	pEntity1 = CreateEntity<DummyEntity>(100, "../../../res/Ball.png", assetManager);
	pEntity1->SetPosition(500, 300);

	pEntity2 = CreateEntity<DummyEntity>(100, 100, "../../../res/car.png", assetManager);
	pEntity2->SetPosition(100, 100);

	pEntitySelected = nullptr;
}

void SampleScene::OnEvent(const sf::Event& event)
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

void SampleScene::TrySetSelectedEntity(DummyEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void SampleScene::OnUpdate()
{
	pEntity2->SetDirection(1.f, 0.f, 50.f);
	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
}