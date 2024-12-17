#include "pch.h"

#include "SampleScene.h"

#include "DummyEntity.h"
#include "EnemyEntity.h"
#include "StalkerEntity.h"
#include "KamikazeEntity.h"
#include "ShooterEntity.h"
#include "LanerEntity.h"
#include "PlayerEntity.h"
#include "BossEntity.h"

#include "EnemyBullet.h"
#include "LanerBullet.h"

#include "Bullet.h"
#include "HomingBullet.h"
#include "RocketBullet.h"

#include "Debug.h"

#include "AssetManager.h"

void SampleScene::OnInitialize()
{
	AssetManager assetManager;

	/*pEntity1 = CreateEntity<DummyEntity>(100, 100, "../../../res/spritesheet.png", 4, 4, 1.0f);
	pEntity1->SetAnimatedSpriteType(Entity::AnimatedSpriteType::AnimatedSprite);
	pEntity1->GetTexture();
	pEntity1->SetPosition(500, 100);*/
  
	/*pDummy.push_back(CreateEntity<DummyEntity>(100, sf::Color::Red));
	pDummy.back()->SetPosition(1000, 100);
	pDummy.back()->SetTag(Tag::ENNEMIES);*/

	/*pEnemy.push_back(CreateEntity<EnemyEntity>(100, sf::Color::Red));
	pEnemy.back()->SetPosition(1000, 300);
	pEnemy.back()->SetTag(Tag::ENNEMIES);*/

	pStalker.push_back(CreateEntity<StalkerEntity>(40, 40, "../../../res/stalker.png", 1, 1, 1.0f));
	pStalker.back()->SetCollisionType(Entity::CollisionType::AABB);
	pStalker.back()->SetTag(Tag::ENNEMIES);

	pKamikaze.push_back(CreateEntity<KamikazeEntity>(30, 30, "../../../res/kamikaze.png", 1, 1, 1.0f));
	pKamikaze.back()->SetCollisionType(Entity::CollisionType::AABB);
	pKamikaze.back()->SetPosition(1000, 500);
	pKamikaze.back()->SetTarget(pPlayer);
	pKamikaze.back()->SetTag(Tag::ENNEMIES);

	pShooter.push_back(CreateEntity<ShooterEntity>(50, 50, "../../../res/shooter.png", 1, 1, 1.0f));
	pShooter.back()->SetCollisionType(Entity::CollisionType::AABB);
	pShooter.back()->SetPosition(1000, 500);
	pShooter.back()->SetTag(Tag::ENNEMIES);

	pLaner.push_back(CreateEntity<LanerEntity>(60, 60, "../../../res/laner.png", 1, 1, 1.0f));
	pLaner.back()->SetCollisionType(Entity::CollisionType::AABB);
	pLaner.back()->SetPosition(1000, 600);
	pLaner.back()->SetTag(Tag::ENNEMIES);

	pBoss.push_back(CreateEntity<BossEntity>(200, 200, "../../../res/boss.png", 1, 1, 1.0f));
	pBoss.back()->SetCollisionType(Entity::CollisionType::AABB);
	pBoss.back()->SetPosition(1000, 350);
	pBoss.back()->SetTag(Tag::ENNEMIES);

	pPlayer = CreateEntity<PlayerEntity>(50, 50, "../../../res/player.png", 1, 1, 1.0f);
	pPlayer->SetCollisionType(Entity::CollisionType::AABB);
	pPlayer->SetPosition(500, 350);
	pPlayer->SetTag(Tag::PLAYER);

	// Ajouter toutes les entités ennemies dans pAllEnemies
	for (auto& dummy : pDummy) {
		pAllEnemies.push_back(dummy);
	}
	for (auto& enemy : pEnemy) {
		pAllEnemies.push_back(enemy);
	}
	for (auto& stalker : pStalker) {
		pAllEnemies.push_back(stalker);
	}
	for (auto& kamikaze : pKamikaze) {
		pAllEnemies.push_back(kamikaze);
	}
	for (auto& shooter : pShooter) {
		pAllEnemies.push_back(shooter);
	}
	for (auto& laner : pLaner) {
		pAllEnemies.push_back(laner);
	}
	for (auto& boss : pBoss) {
		pAllEnemies.push_back(boss);
	}

	for (auto& stalker : pStalker) {
		stalker->mPlayer = pPlayer;
	}

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
				pHoming.push_back(CreateEntity<HomingBulletEntity>(20, 20, "../../../res/homing.png", 1, 1, 1.0f));
				pHoming.back()->SetCollisionType(Entity::CollisionType::AABB);
				for (auto& enemy : pAllEnemies) {
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
			pRocket.push_back(CreateEntity<RocketBulletEntity>(20, 20, "../../../res/rocket.png", 1, 1, 1.0f));
			pRocket.back()->SetCollisionType(Entity::CollisionType::AABB);
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
			return;
		}
	}

	for (auto& player : pDummy) {
		if (player->IsInside(x, y)) {
			pEntitySelected = player;
			return;
		}
	}

	pEntitySelected = nullptr;
}

void SampleScene::OnUpdate()
{
	float playerShootCooldown = 0.1f;
	float shooterShootCooldown = 1;
	float lanerShootCooldown = 6;

	timeSinceLastShot += GameManager::Get()->GetDeltaTime();
	timeSinceLastEnemyShot += GameManager::Get()->GetDeltaTime();
	timeSinceLastLanerShot += GameManager::Get()->GetDeltaTime();

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

	//----------Creation des projectiles du joueur----------

	pPx = pPlayer->GetPosition().x + 35;
	pPy = pPlayer->GetPosition().y;

	//Basique
	if (timeSinceLastShot >= playerShootCooldown) 
	{
		pProjectiles.push_back(CreateEntity<BulletEntity>(10, 10, "../../../res/bullet.png", 1, 1, 1.0f));
		pProjectiles.back()->SetCollisionType(Entity::CollisionType::Circle);
		pProjectiles.back()->SetPosition(pPx, pPy);

		timeSinceLastShot = 0.0f;
	}

	//Homing
	for (size_t i = 0; i < pHoming.size(); ++i)
	{
		for (auto& enemy : pAllEnemies)
		{
			if (enemy->IsTag(SampleScene::Tag::ENNEMIES))
			{
				pHoming[i]->SetTarget(enemy);
				break;
			}
		}
	}

	//----------Création des projectiles des ennemies----------

	//Shooter
	if (timeSinceLastEnemyShot >= shooterShootCooldown)
	{
		for (auto it = pShooter.begin(); it != pShooter.end(); )
		{
			ShooterEntity* shooter = *it;

			if (shooter->ToDestroy()) {
				it = pShooter.erase(it);
				continue;
			}

			if (shooter->IsTag(Tag::ENNEMIES)) {
				sf::Vector2f shooterPosition = shooter->GetPosition();
				sf::Vector2f playerPosition = pPlayer->GetPosition();

				pEnemyProjectiles.push_back(CreateEntity<EnemyBulletEntity>(10, 10, "../../../res/ennemybullet.png", 1, 1, 1.0f));
				pEnemyProjectiles.back()->SetCollisionType(Entity::CollisionType::AABB);
				pEnemyProjectiles.back()->SetPosition(shooterPosition.x, shooterPosition.y);
				pEnemyProjectiles.back()->SetTarget(pPlayer);
			}

			++it;
		}
		timeSinceLastEnemyShot = 0.0f;
	}

	//Kamikase (c'est lui le missile :)
	for (size_t i = 0; i < pKamikaze.size(); ++i)
	{
		if (pPlayer->IsTag(SampleScene::Tag::PLAYER))
		{
			pKamikaze[i]->SetTarget(pPlayer);
			break;
		}
	}
	//Laner
	if (timeSinceLastLanerShot >= lanerShootCooldown)
	{
		for (auto& laner : pLaner)
		{
			if (laner->IsTag(Tag::ENNEMIES))
			{
				sf::Vector2f lanerPosition = laner->GetPosition();

				pLanerProjectiles.push_back(CreateEntity<LanerBulletEntity>(20, 20, "../../../res/lanerbullet.png", 1, 1, 1.0f));
				pLanerProjectiles.back()->SetCollisionType(Entity::CollisionType::AABB);
				pLanerProjectiles.back()->SetPosition(lanerPosition.x, lanerPosition.y);
			}
		}
	}
	//----------Déplacement----------
	float dt = GameManager::Get()->GetDeltaTime();
	sf::Vector2f velocity = direction * (speed * dt);

	x += velocity.x;
	y += velocity.y;

	pPlayer->SetPosition(x, y);
}