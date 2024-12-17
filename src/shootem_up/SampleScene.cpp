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

void SampleScene::OnInitialize()
{
	pPlayer = CreateEntity<PlayerEntity>(25, sf::Color::White);
	pPlayer->SetPosition(500, 350);
	pPlayer->SetTag(Tag::PLAYER);

	/*pStalker.push_back(CreateEntity<StalkerEntity>(40, sf::Color::Red));
	pStalker.back()->SetTag(Tag::ENNEMIES);

	pKamikaze.push_back(CreateEntity<KamikazeEntity>(30, sf::Color::Red));
	pKamikaze.back()->SetPosition(1000, 500);
	pKamikaze.back()->SetTarget(pPlayer);
	pKamikaze.back()->SetTag(Tag::ENNEMIES);

	pShooter.push_back(CreateEntity<ShooterEntity>(50, sf::Color::Red));
	pShooter.back()->SetPosition(1000, 500);
	pShooter.back()->SetTarget(pPlayer);
	pShooter.back()->SetTag(Tag::ENNEMIES);

	pLaner.push_back(CreateEntity<LanerEntity>(60, sf::Color::Red));
	pLaner.back()->SetPosition(1000, 600);
	pLaner.back()->SetTag(Tag::ENNEMIES);*/

	pBoss.push_back(CreateEntity<BossEntity>(200, sf::Color::Magenta));
	pBoss.back()->SetPosition(1000, 350);
	pBoss.back()->SetTarget(pPlayer);
	pBoss.back()->SetTag(Tag::ENNEMIES);

	

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

	std::ifstream inputFile("../../../res/Level1.txt");

	std::string line;


	while (std::getline(inputFile, line)) {
		if (!line.empty()) 
		{
			waves.push_back(line);
		}
	}

	inputFile.close();

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
	pPx = pPlayer->GetPosition().x;
	pPx = pPlayer->GetPosition().x;
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
	float bossShootCooldown = 0.5;

	timeSinceLastShot += GameManager::Get()->GetDeltaTime();
	timeSinceLastEnemyShot += GameManager::Get()->GetDeltaTime();
	timeSinceLastLanerShot += GameManager::Get()->GetDeltaTime();
	timeSinceLastBossShot += GameManager::Get()->GetDeltaTime();

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

	//Supression et debug des Projectiles

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

	//----------Creation des projectiles du joueur----------

	pPx = pPlayer->GetPosition().x + 35;
	pPy = pPlayer->GetPosition().y;

	//Basique
	if (timeSinceLastShot >= playerShootCooldown) 
	{
		pProjectiles.push_back(CreateEntity<BulletEntity>(5, sf::Color::Yellow));
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

			shooter->Shoot();

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
			laner->Shoot();
		}
	}

	//----------Déplacement----------
	float dt = GameManager::Get()->GetDeltaTime();
	sf::Vector2f velocity = direction * (speed * dt);

	x += velocity.x;
	y += velocity.y;

	pPlayer->SetPosition(x, y);

	Timer += dt;
	if (Timer > 4) {
		if (currentWaveIndex < waves.size()) {
			ProcessWave(waves[currentWaveIndex]);
			currentWaveIndex++; 
		}
		Timer = 0;
	}
}


void SampleScene::ProcessWave(const std::string& wave) {

	int index = 0; 
	for (char c : wave) {
		if (index <= 5) {
			std::cout << c << std::endl;
			++index;
			if (c == '-') {
				std::cout << "Nothing Summoned" << std::endl;
				continue;
			}

			float xPosition = 1000.0f; 
			float yPosition = (144.0f * index) - 72;

			if (c == 'S') {
				// Summon Ennemi Set Path
				std::cout << "Summoned Set Path" << std::endl;
				continue;
			}
			if (c == 'D') {
				// Summon Ennemi Default
				pEnemy.push_back(CreateEntity<EnemyEntity>(100, sf::Color::Red));
				pEnemy.back()->SetPosition(xPosition, yPosition);
				pEnemy.back()->SetTag(Tag::ENNEMIES);
				std::cout << "Summoned Default" << std::endl;
				continue;
			}
			if (c == 'K') {
				// Summon Ennemi Kamikaze
				std::cout << "Summoned Kamikaze" << std::endl;
				continue;
			}
			if (c == 'C') {
				// Summon Ennemi Chercheuse
				std::cout << "Summoned Heat Seaking" << std::endl;
				continue;
			}
			if (c == 'L') {
				// Summon Ennemi Lazer
				std::cout << "Summoned Lazer" << std::endl;
				continue;
			}
			if (c == 'B') {
				// Summon Ennemi Blocking
				std::cout << "Summoned Blocking" << std::endl;
				continue;
			}
			std::cout << "Summoning next wave" << std::endl;
		}
	}
}