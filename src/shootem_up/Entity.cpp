#include "pch.h"

#include "Entity.h"

#include "GameManager.h"
#include "Utils.h"

#include <SFML/Graphics.hpp>
#include <iostream>

void Entity::Initialize(float _w, const char* _path, AssetManager& assetManager)
{
	Texture* texture = assetManager.GetTexture(_path);
	if (!texture) {
		std::cout << "Failed to load texture: " << _path << std::endl;
		return;
	}

	mTexture = *texture->GetTexture();
	mTexture.setSmooth(true);
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(0, 0);
	float scale = _w / mSprite.getTexture()->getSize().x;
	SetScale(scale, scale);

	mCollisionType = CollisionType::Circle;

	mDirection = sf::Vector2f(0.0f, 0.0f);
	mSpeed = 0.0f;
	mToDestroy = false;
	mTag = -1;
	mTarget.isSet = false;
}

void Entity::Initialize(float _w, float _h, const char* _path, AssetManager& assetManager)
{
	Texture* texture = assetManager.GetTexture(_path);
	if (texture == nullptr) {
		std::cout << "Failed to load texture: " << _path << std::endl;
		return;
	}

	mTexture = *texture->GetTexture();
	mTexture.setSmooth(true);
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(0, 0);
	SetSizeWH(_w, _h);

	mCollisionType = CollisionType::AABB;

	mDirection = sf::Vector2f(0.0f, 0.0f);
	mSpeed = 0.0f;
	mToDestroy = false;
	mTag = -1;
	mTarget.isSet = false;
}

bool Entity::IsCollidingCircleCircle(Entity* other) const
{
	sf::Vector2f distance = GetPosition(0.5f, 0.5f) - other->GetPosition(0.5f, 0.5f);

	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);

	float radius1 = mShape.getRadius();
	float radius2 = other->mShape.getRadius();

	float sqrRadius = (radius1 + radius2) * (radius1 + radius2);

	return sqrLength < sqrRadius;
}

bool Entity::IsCollidingRectRect(Entity* other) const
{
	sf::Vector2f pos1 = GetPosition();
	sf::Vector2f size1(mShape.getRadius(), mShape.getRadius());
	/*sf::Vector2f size1(mShape.getGlobalBounds().width, mShape.getGlobalBounds().height);*/
	sf::Vector2f pos2 = other->GetPosition();
	sf::Vector2f size2(other->mShape.getRadius(), other->mShape.getRadius());
	/*sf::Vector2f size2(other->mShape.getGlobalBounds().width, other->mShape.getGlobalBounds().height);*/

	if (!(pos1.y - size1.y > pos2.y + size2.y) &&
		!(pos1.y + size1.y < pos2.y - size2.y) &&
		!(pos1.x - size1.x > pos2.x + size2.x) &&
		!(pos1.x + size1.x < pos2.x - size2.x))
	{
		return true;
	}
	return false;
}

bool Entity::IsCollidingCircleRect(Entity* other) const
{
	if (!other) return false;

	// 1. Vérification rapide (rectangle englobant)
	float radius = mShape.getRadius();
	sf::Vector2f circlePos = GetPosition(0.5f, 0.5f); // Centre du cercle
	sf::Vector2f circleBoundsPos(circlePos.x - radius, circlePos.y - radius); // Position du rectangle englobant
	sf::Vector2f circleBoundsSize(radius * 2, radius * 2); // Taille du rectangle englobant

	// Rectangle englobant du cercle
	Entity circleBoundingBox;
	circleBoundingBox.SetPosition(circleBoundsPos.x, circleBoundsPos.y);
	circleBoundingBox.SetSize(circleBoundsSize.x, circleBoundsSize.y);

	if (!circleBoundingBox.IsCollidingRectRect(other))
	{
		return false; // Pas d'intersection au niveau des rectangles englobants
	}

	// 2. Vérification précise (cercle-rectangle)
	sf::Vector2f rectPos = other->GetPosition();
	sf::Vector2f rectSize(other->mShape.getGlobalBounds().width, other->mShape.getGlobalBounds().height);

	// Trouver le point le plus proche sur le rectangle
	float closestX = std::clamp(circlePos.x, rectPos.x, rectPos.x + rectSize.x);
	float closestY = std::clamp(circlePos.y, rectPos.y, rectPos.y + rectSize.y);

	// Calculer la distance entre le centre du cercle et ce point
	float distanceX = circlePos.x - closestX;
	float distanceY = circlePos.y - closestY;
	float distanceSquared = distanceX * distanceX + distanceY * distanceY;

	return distanceSquared <= (radius * radius);
}


bool Entity::IsInside(float x, float y) const
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	float dx = x - position.x;
	float dy = y - position.y;

	float radius = mShape.getRadius();

	return (dx * dx + dy * dy) < (radius * radius);
}

bool Entity::IsColliding(Entity* other) const
{
	switch (mCollisionType)
	{
	case CollisionType::Circle:
		switch (other->mCollisionType)
		{
		case CollisionType::Circle:
			return IsCollidingCircleCircle(other);
		case CollisionType::AABB:
			return IsCollidingCircleRect(other);
		}
	case CollisionType::AABB:
		switch (other->mCollisionType)
		{
		case CollisionType::Circle:
			return IsCollidingCircleRect(other);
		case CollisionType::AABB:
			return IsCollidingRectRect(other);
		}
	}
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{
	sf::Vector2f size(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);

	x -= size.x * ratioX;
	y -= size.y * ratioY;

	mSprite.setPosition(x, y);
	mShape.setPosition(x, y);
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f size(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
	sf::Vector2f position = mShape.getPosition();

	position.x += size.x * ratioX;
	position.y += size.y * ratioY;

	return position;
}

bool Entity::GoToDirection(int x, int y, float speed)
{
	if(speed > 0)
		mSpeed = speed+100;

	sf::Vector2f position = GetPosition(0.5f, 0.5f);
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	mDirection = direction;

	return true;
}

bool Entity::GoToPosition(int x, int y, float speed)
{
	if (GoToDirection(x, y, speed) == false)
		return false;

	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	mTarget.position = { x, y };
	mTarget.distance = Utils::GetDistance(position.x, position.y, x, y);
	mTarget.isSet = true;

	return true;
}

void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		mSpeed = speed;

	mDirection = sf::Vector2f(x, y);
}

void Entity::SetSize(float x, float y)
{
	// Création du vecteur
	sf::Vector2f size(x, y);

	// Si Entity = Rectangle
	if (auto* rectShape = dynamic_cast<sf::RectangleShape*>(&mShape))
	{
		rectShape->setSize(size);
	}

	// Si Entity = Circle (diamètre = largeur = hauteur)
	else if (auto* circleShape = dynamic_cast<sf::CircleShape*>(&mShape))
	{
		float diameter = std::min(x, y);
		circleShape->setRadius(diameter / 2.0f);
		circleShape->setOrigin(diameter / 2.0f, diameter / 2.0f);
	}
}

void Entity::Update()
{
	float dt = GetDeltaTime();
	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;
	mShape.move(translation);
	mSprite.move(translation);

	if (mTarget.isSet) 
	{
		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			SetPosition(mTarget.position.x, mTarget.position.y, 0.5f, 0.5f);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}

	OnUpdate();
}

Scene* Entity::GetScene() const
{
	return GameManager::Get()->GetScene();
}

float Entity::GetDeltaTime() const
{
	return GameManager::Get()->GetDeltaTime();
}

void Entity::DrawCollision(sf::RenderWindow* window) const
{
	if (mCollisionType == CollisionType::Circle)
	{
		sf::CircleShape circle(GetRadius());
		circle.setPosition(GetPosition(0.5f, 0.5f) - sf::Vector2f(GetRadius(), GetRadius()));
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(sf::Color::Red);
		circle.setOutlineThickness(1.0f);
		window->draw(circle);
	}
	else if (mCollisionType == CollisionType::AABB)
	{
		sf::RectangleShape rectangle(sf::Vector2f(SpriteGetWidth(), SpriteGetHeight()));
		rectangle.setPosition(GetPosition(0.5f, 0.5f) - sf::Vector2f(SpriteGetWidth() / 2, SpriteGetHeight() / 2));
		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setOutlineColor(sf::Color::Red);
		rectangle.setOutlineThickness(1.0f);
		window->draw(rectangle);
	}
}