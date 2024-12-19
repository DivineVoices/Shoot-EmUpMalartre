#include "pch.h"

#include "SampleScene.h"
#include "AssetManager.h"
#include "AudioManager.h"	

#include "DummyEntity.h"
#include "EnemyEntity.h"
#include "StalkerEntity.h"
#include "KamikazeEntity.h"
#include "ShooterEntity.h"
#include "LanerEntity.h"
#include "PlayerEntity.h"
#include "BossEntity.h"

#include "Coin.h"

#include "EnemyBullet.h"
#include "LanerBullet.h"

#include "Bullet.h"
#include "HomingBullet.h"
#include "RocketBullet.h"

#include "Debug.h"



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

	//pStalker.push_back(CreateEntity<StalkerEntity>(40, 40, "../../../res/stalker.png", 1, 1, 1.0f));
	//pStalker.back()->SetCollisionType(Entity::CollisionType::AABB);
	//pStalker.back()->SetTag(Tag::ENNEMIES);

	//pKamikaze.push_back(CreateEntity<KamikazeEntity>(30, 30, "../../../res/kamikaze.png", 1, 1, 1.0f));
	//pKamikaze.back()->SetCollisionType(Entity::CollisionType::AABB);
	//pKamikaze.back()->SetPosition(1000, 500);
	//pKamikaze.back()->SetTarget(pPlayer);
	//pKamikaze.back()->SetTag(Tag::ENNEMIES);

	//pShooter.push_back(CreateEntity<ShooterEntity>(50, 50, "../../../res/shooter.png", 1, 1, 1.0f));
	//pShooter.back()->SetCollisionType(Entity::CollisionType::AABB);
	//pShooter.back()->SetPosition(1000, 500);
	//pShooter.back()->SetTag(Tag::ENNEMIES);

	//pLaner.push_back(CreateEntity<LanerEntity>(60, 60, "../../../res/laner.png", 1, 1, 1.0f));
	//pLaner.back()->SetCollisionType(Entity::CollisionType::AABB);
	//pLaner.back()->SetPosition(1000, 600);
	//pLaner.back()->SetTag(Tag::ENNEMIES);

	//pBoss.push_back(CreateEntity<BossEntity>(200, 200, "../../../res/boss.png", 1, 1, 1.0f));
	//pBoss.back()->SetCollisionType(Entity::CollisionType::AABB);
	//pBoss.back()->SetPosition(1000, 350);
	//pBoss.back()->SetTag(Tag::ENNEMIES);

	/*pCoin.push_back(CreateEntity<CoinEntity>(25, sf::Color::Yellow));
	pCoin.back()->SetPosition(1000, 350);*/

	pDummy.push_back(CreateEntity<DummyEntity>(3840, 720, "../../../res/etoiles.png", 1, 1, 1.0f));
	pDummy.back()->SetPosition(100, BackY);
	pDummy[0]->GoToPosition(GoalX, BackY, BackSpeed);
	pDummy.push_back(CreateEntity<DummyEntity>(3840, 720, "../../../res/etoiles.png", 1, 1, 1.0f));
	pDummy.back()->SetPosition(2660, BackY);
	pDummy[1]->GoToPosition(GoalX, BackY, BackSpeed);

	pDummy.push_back(CreateEntity<DummyEntity>(180, 180, "../../../res/saturne.png", 1, 1, 1.0f));
	pDummy.back()->SetPosition(100, PlanetY);
	pDummy[2]->GoToPosition(GoalX, PlanetY, PlanetSpeed);
	pDummy.push_back(CreateEntity<DummyEntity>(180, 180, "../../../res/saturne.png", 1, 1, 1.0f));
	pDummy.back()->SetPosition(2660, PlanetY);
	pDummy[3]->GoToPosition(GoalX, PlanetY, PlanetSpeed);

	pDummy.push_back(CreateEntity<DummyEntity>(2560, 540, "../../../res/route.png", 1, 1, 1.0f));
	pDummy.back()->SetPosition(200, RoadY);
	pDummy[4]->GoToPosition(GoalX, RoadY, RoadSpeed);
	pDummy.push_back(CreateEntity<DummyEntity>(2560, 540, "../../../res/route.png", 1, 1, 1.0f));
	pDummy.back()->SetPosition(2660, RoadY);
	pDummy[5]->GoToPosition(GoalX, RoadY, RoadSpeed);

	pDummy.push_back(CreateEntity<DummyEntity>(1440, 256, "../../../res/paraback.png", 1, 1, 1.0f));
	pDummy.back()->SetPosition(100, CityY);
	pDummy[6]->GoToPosition(GoalX, CityY, CitySpeed2);
	pDummy.push_back(CreateEntity<DummyEntity>(1440, 256, "../../../res/paraback.png", 1, 1, 1.0f));
	pDummy.back()->SetPosition(1540, CityY);
	pDummy[7]->GoToPosition(GoalX, CityY, CitySpeed2);

	pDummy.push_back(CreateEntity<DummyEntity>(1440, 256, "../../../res/parafront.png", 1, 1, 1.0f));
	pDummy.back()->SetPosition(100, CityY);
	pDummy[8]->GoToPosition(GoalX, CityY, CitySpeed);
	pDummy.push_back(CreateEntity<DummyEntity>(1440, 256, "../../../res/parafront.png", 1, 1, 1.0f));
	pDummy.back()->SetPosition(1540, CityY);
	pDummy[9]->GoToPosition(GoalX, CityY, CitySpeed);

	pPlayer = CreateEntity<PlayerEntity>(87.5f, 30, "../../../res/player.png", 1, 1, 1.0f);
	pPlayer->SetCollisionType(Entity::CollisionType::AABB);
	pPlayer->SetPosition(500, 350);
	pPlayer->SetTag(Tag::PLAYER);

	for (auto& dummy : pDummy) {
		dummy->SetTag(2);
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

	AudioManager::Get()->PlayMusic("../../../res/maintheme.mp3");
	AudioManager::Get()->SetMusicVolume(5.0f);
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

	if (gameOver && event.key.code == sf::Keyboard::Space)
	{
		RestartGame();
		return;
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

	timeSinceLastShot += GameManager::Get()->GetDeltaTime();

	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}

	//Lanes pour le débug
	/*for (int i = 0; i < 5; i++)
	{
		const AABB& aabb = mAreas[i];

		Debug::DrawRectangle(aabb.xMin, aabb.yMin, aabb.xMax - aabb.xMin, aabb.yMax - aabb.yMin, sf::Color::White);
	}*/

	//----------Creation des projectiles du joueur----------

	pPx = pPlayer->GetPosition().x + 35;
	pPy = pPlayer->GetPosition().y;

	//Basique
	if (timeSinceLastShot >= playerShootCooldown) 
	{
		pProjectiles.push_back(CreateEntity<BulletEntity>(10, 10, "../../../res/bullet.png", 1, 1, 1.0f));
		pProjectiles.back()->SetCollisionType(Entity::CollisionType::AABB);
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

	//----------Vider les vecteurs si Destroy----------

	//Ennemies

	//Shooter
	for (auto it = pShooter.begin(); it != pShooter.end(); )
	{
		ShooterEntity* shooter = *it;

		if (shooter->ToDestroy()) {
			it = pShooter.erase(it);
			continue;
		}
		++it;
		}

	//Laner
	for (auto it = pLaner.begin(); it != pLaner.end(); )
	{
		LanerEntity* laner = *it;

		if (laner->ToDestroy()) {
			it = pLaner.erase(it);
			continue;
		}
		++it;
	}

	//Kamikaze
	for (auto it = pKamikaze.begin(); it != pKamikaze.end(); )
	{
		KamikazeEntity* kamikaze = *it;

		if (kamikaze->ToDestroy()) {
			it = pKamikaze.erase(it);
			continue;
		}
		++it;
	}

	//Boss
	for (auto it = pBoss.begin(); it != pBoss.end(); )
	{
		BossEntity* boss = *it;

		if (boss->ToDestroy()) {
			it = pBoss.erase(it);
			continue;
		}
		++it;
	}

	//Ennemies
	for (auto it = pEnemy.begin(); it != pEnemy.end(); )
	{
		EnemyEntity* enemy = *it;

		if (enemy->ToDestroy()) {
			it = pEnemy.erase(it);
			continue;
		}
		++it;
	}

	//Bullet

	//Homing
	for (auto it = pHoming.begin(); it != pHoming.end(); )
	{
		HomingBulletEntity* homing = *it;

		if (homing->ToDestroy()) {
			it = pHoming.erase(it);
			continue;
		}
		++it;
	}

	//Projectiles enemies basique
	for (auto it = pEnemyProjectiles.begin(); it != pEnemyProjectiles.end(); )
	{
		EnemyBulletEntity* badbullet = *it;

		if (badbullet->ToDestroy()) {
			it = pEnemyProjectiles.erase(it);
			continue;
		}
		++it;
	}

	//Projectiles enemies laner
	for (auto it = pLanerProjectiles.begin(); it != pLanerProjectiles.end(); )
	{
		LanerBulletEntity* badlanerbullet = *it;

		if (badlanerbullet->ToDestroy()) {
			it = pLanerProjectiles.erase(it);
			continue;
		}
		++it;
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

	//----------Déplacement----------
	float dt = GameManager::Get()->GetDeltaTime();
	sf::Vector2f velocity = direction * (speed * dt);

	x += velocity.x;
	y += velocity.y;

	pPlayer->SetPosition(x, y);

	//----------Arrivée des vagues d'ennemies----------
	Timer += dt;
	if (Timer > 4.5f) {
		if (currentWaveIndex < waves.size()) {
			ProcessWave(waves[currentWaveIndex]);
			currentWaveIndex++; 
		}
		Timer = 0;
	}

	//----------Ecran game over, Pause et de victoire----------
	if (pPlayer->GetLife() <= 0 && !gameOver)
	{
		pDummy.push_back(CreateEntity<DummyEntity>(1300, 720, "../../../res/loose.png", 1, 1, 1.0f));
		pDummy.back()->SetPosition(650, 360);
		pDummy.back()->SetTag(2);

		pDummy.push_back(CreateEntity<DummyEntity>(560, 360, "../../../res/loosetext.png", 1, 1, 1.0f));
		pDummy.back()->SetPosition(650, 360);
		pDummy.back()->SetTag(2);
		gameOver = true;
	}

	static bool bossSpawned = false;
	
	if (!bossSpawned) {

		if (!pBoss.empty() && pBoss[0] != nullptr) {
			bossSpawned = true;
			std::cout << "Boss spawned!" << std::endl;
		}
	}

	if (bossSpawned && pBoss.empty()) {
		std::cout << "Boss has been destroyed or is null!" << std::endl;

		if (pPlayer->GetLife() > 0 && !gameOver) {
			pDummy.push_back(CreateEntity<DummyEntity>(1300, 720, "../../../res/victory.png", 1, 1, 1.0f));
			pDummy.back()->SetPosition(650, 360);
			pDummy.back()->SetTag(2);

			pDummy.push_back(CreateEntity<DummyEntity>(560, 360, "../../../res/victorytext.png", 1, 1, 1.0f));
			pDummy.back()->SetPosition(650, 360);
			pDummy.back()->SetTag(2);
			if (pPlayer->GetCoinNumber() == 6)
			{
				pDummy.push_back(CreateEntity<DummyEntity>(280, 180, "../../../res/coin.png", 1, 1, 1.0f));
				pDummy.back()->SetPosition(650, 560);
				pDummy.back()->SetTag(2);
			}
			gameOver = true;
			bossSpawned = false;
		}
	}

	/*
	if (pBoss.back()->GetLife() <= 0)
	{
		for (auto& coin : pCoin) {
			if (coin) {
				coinNumber = coin->GetCoinNumber();
				std::cout << "Coins collected: " << coinNumber << std::endl;
			}
		}

		if (coinNumber == 5)
		{

		}
	}
	*/

	//----------FX/UI----------
	if (pDummy[0]->GetPosition().x <= -1390)
	{
		pDummy[0]->SetPosition(2660, BackY);
		pDummy[0]->GoToPosition(GoalX, BackY, BackSpeed);
	}
	if (pDummy[1]->GetPosition().x <= -1390)
	{
		pDummy[1]->SetPosition(2660, BackY);
		pDummy[1]->GoToPosition(GoalX, BackY, BackSpeed);
	}
	if (pDummy[2]->GetPosition().x <= -1390)
	{
		pDummy[2]->SetPosition(2660, PlanetY);
		pDummy[2]->GoToPosition(GoalX, PlanetY, PlanetSpeed);
	}
	if (pDummy[3]->GetPosition().x <= -1390)
	{
		pDummy[3]->SetPosition(2660, PlanetY);
		pDummy[3]->GoToPosition(GoalX, PlanetY, PlanetSpeed);
	}
	if (pDummy[4]->GetPosition().x <= -1390)
	{
		pDummy[4]->SetPosition(2660, RoadY);
		pDummy[4]->GoToPosition(GoalX, RoadY, RoadSpeed);
	}
	if (pDummy[5]->GetPosition().x <= -1390)
	{
		pDummy[5]->SetPosition(2660, RoadY);
		pDummy[5]->GoToPosition(GoalX, RoadY, RoadSpeed);
	}
	if (pDummy[6]->GetPosition().x <= -890)
	{
		pDummy[6]->SetPosition(2000, CityY);
		pDummy[6]->GoToPosition(GoalX, CityY, CitySpeed2);
	}
	if (pDummy[7]->GetPosition().x <= -890)
	{
		pDummy[7]->SetPosition(2000, CityY);
		pDummy[7]->GoToPosition(GoalX, CityY, CitySpeed2);
	}
	if (pDummy[8]->GetPosition().x <= -890)
	{
		pDummy[8]->SetPosition(2000, CityY);
		pDummy[8]->GoToPosition(GoalX, CityY, CitySpeed);
	}
	if (pDummy[9]->GetPosition().x <= -890)
	{
		pDummy[9]->SetPosition(2000, CityY);
		pDummy[9]->GoToPosition(GoalX, CityY, CitySpeed);
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

			float xPosition = 1150.0f; 
			float yPosition = (144.0f * index) - 72;

			if (c == 'S') {
				// Summon Ennemi Set Path
				std::cout << "Summoned Set Path" << std::endl;
				continue;
			}
			if (c == 'D') {
				// Summon Ennemi Default
				pShooter.push_back(CreateEntity<ShooterEntity>(50, 50, "../../../res/shooter.png", 1, 1, 1.0f));
				pShooter.back()->SetCollisionType(Entity::CollisionType::AABB);
				pShooter.back()->SetPosition(xPosition, yPosition);
				pShooter.back()->SetTarget(pPlayer);
				pShooter.back()->SetTag(Tag::ENNEMIES);
				std::cout << "Summoned Default" << std::endl;
				continue;
			}
			if (c == 'K') {
				// Summon Ennemi Kamikaze
				pKamikaze.push_back(CreateEntity<KamikazeEntity>(30, 30, "../../../res/kamikaze.png", 1, 1, 1.0f));
				pKamikaze.back()->SetCollisionType(Entity::CollisionType::AABB);
				pKamikaze.back()->SetPosition(xPosition, yPosition);
				pKamikaze.back()->SetTarget(pPlayer);
				pKamikaze.back()->SetTag(Tag::ENNEMIES);
				std::cout << "Summoned Kamikaze" << std::endl;
				continue;
			}
			if (c == 'C') {
				// Summon Pieces
				pCoin.push_back(CreateEntity<CoinEntity>(30, 30, "../../../res/coin.png", 1, 1, 1.0f));
				pCoin.back()->SetCollisionType(Entity::CollisionType::AABB);
				pCoin.back()->SetPosition(xPosition, yPosition);
				pCoin.back()->SetTag(Tag::COIN);
				std::cout << "Summoned Coin" << std::endl;
				continue;
			}
			if (c == 'L') {
				// Summon Ennemi Lazer
				pLaner.push_back(CreateEntity<LanerEntity>(60, 60, "../../../res/laner.png", 1, 1, 1.0f));
				pLaner.back()->SetCollisionType(Entity::CollisionType::AABB);
				pLaner.back()->SetPosition(xPosition, yPosition);
				pLaner.back()->SetTag(Tag::ENNEMIES); 
				std::cout << "Summoned Lazer" << std::endl;
				continue;
			}
			if (c == 'B') {
				// Summon Ennemi Blocking
				pStalker.push_back(CreateEntity<StalkerEntity>(40, 40, "../../../res/stalker.png", 1, 1, 1.0f));
				pStalker.back()->SetCollisionType(Entity::CollisionType::AABB);
				pStalker.back()->SetPosition(xPosition, yPosition);
				pStalker.back()->SetTag(Tag::ENNEMIES);
				std::cout << "Summoned Blocking" << std::endl;
				continue;
			}
			if (c == 'F') {
				// Summon Ennemi Boss Final
				pBoss.push_back(CreateEntity<BossEntity>(200, 200, "../../../res/boss.png", 1, 1, 1.0f));
				pBoss.back()->SetCollisionType(Entity::CollisionType::AABB);
				pBoss.back()->SetPosition(xPosition, 350);
				pBoss.back()->SetTarget(pPlayer);
				pBoss.back()->SetTag(Tag::ENNEMIES);
				std::cout << "Summoned Boss Final" << std::endl;
				continue;
			}
			std::cout << "Summoning next wave" << std::endl;
		}
	}
	for (auto& stalker : pStalker) {
		stalker->mPlayer = pPlayer;
	}
	for (auto& shooter : pShooter) {
		shooter->mPlayer = pPlayer;
	}

	// Ajouter toutes les entités ennemies dans pAllEnemies
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
}

void SampleScene::RestartGame()
{
	for (auto& entity : pDummy) {
		entity->Destroy();
	}

	pDummy.clear();

	pEnemy.clear();
	pShooter.clear();
	pLaner.clear();
	pKamikaze.clear();
	pBoss.clear();
	pHoming.clear();
	pRocket.clear();
	pEnemyProjectiles.clear();
	pLanerProjectiles.clear();

	pPlayer->SetPosition(500, 350);
	pPlayer->SetLife(20);
	gameOver = false;

	currentWaveIndex = 0;
	Timer = 0;

	OnInitialize();
}