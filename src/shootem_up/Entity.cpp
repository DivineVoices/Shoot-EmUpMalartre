#include "pch.h"

#include "Entity.h"

#include "GameManager.h"
#include "Utils.h"

#include <SFML/Graphics.hpp>

void Entity::Initialize(float radius, const sf::Color& color, int shape)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);
	mSpeed = 0.0f;
	mToDestroy = false;
	mTag = -1;

	mShape.setOrigin(0.f, 0.f);
	mShape.setRadius(radius);
	mShape.setFillColor(color);
	
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

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{
	float size = mShape.getRadius() * 2;

	x -= size * ratioX;
	y -= size * ratioY;

	mShape.setPosition(x, y);
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	float size = mShape.getRadius() * 2;
	sf::Vector2f position = mShape.getPosition();

	position.x += size * ratioX;
	position.y += size * ratioY;

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