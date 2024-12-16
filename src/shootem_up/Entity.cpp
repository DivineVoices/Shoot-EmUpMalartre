#include "pch.h"

#include "Entity.h"
#include "Texture.h"

#include "GameManager.h"
#include "Utils.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>

void Entity::Initialize(float _w, float _h, std::string _path, int row, int col, float frameTime)
{
	Texture* texture = AssetManager::Get()->GetTexture(_path); // Texture = sf::sprite
	std::cout << "1";
	if (texture == nullptr) {
		std::cout << "Failed to load texture: " << _path << std::endl;
		assert(texture != nullptr);
		return;
	}
	mTexture = *texture->GetTexture();
	mTexture.setSmooth(true);

	mSprite.setTexture(mTexture);
	mSprite.setOrigin(0, 0);

	SetSizeWH(_w, _h);
	mDirection = sf::Vector2f(0.0f, 0.0f);
	mSpeed = 0.0f;
	mToDestroy = false;
	mTag = -1;
	mTarget.isSet = false;


	mAnimation.row = row;
	mAnimation.col = col;
	mAnimation.indexX = 0;
	mAnimation.animationTime = frameTime;
	mAnimation.indexY = 0;
	mAnimation.progress = 0.f;
}


bool Entity::IsCollidingCircleCircle(Entity* other) const
{
	sf::Vector2f distance = GetPosition(0.5f, 0.5f) - other->GetPosition(0.5f, 0.5f);
	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);

	float radius1 = GetRadius();
	float radius2 = other->GetRadius();
	float sqrRadius = (radius1 + radius2) * (radius1 + radius2);
	if (sqrLength < sqrRadius)
	{
		std::cout << "Collision Circle -> Circle" << std::endl;
	}
	return sqrLength < sqrRadius;
}

bool Entity::IsCollidingRectRect(Entity* other) const
{
	sf::Vector2f position1 = GetPosition(0.5f, 0.5f);
	sf::Vector2f position2 = other->GetPosition(0.5f, 0.5f);

	float sizex1 = SpriteGetWidth();
	float sizey1 = SpriteGetHeight();

	float sizex2 = other->SpriteGetWidth();
	float sizey2 = other->SpriteGetHeight();

	float left1 = position1.x - sizex1 / 2;
	float right1 = position1.x + sizex1 / 2;
	float top1 = position1.y - sizey1 / 2;
	float bottom1 = position1.y + sizey1 / 2;

	float left2 = position2.x - sizex2 / 2;
	float right2 = position2.x + sizex2 / 2;
	float top2 = position2.y - sizey2 / 2;
	float bottom2 = position2.y + sizey2 / 2;
	if (left1 < right2 && right1 > left2 && top1 < bottom2 && bottom1 > top2)
	{
		std::cout << "Collision Rect -> Rect" << std::endl;
	}
	return (left1 < right2 && right1 > left2 && top1 < bottom2 && bottom1 > top2);
}

bool Entity::IsCollidingCircleRect(Entity* other) const
{
	sf::Vector2f position1 = GetPosition(0.5f, 0.5f);
	sf::Vector2f position2 = other->GetPosition(0.5f, 0.5f);

	float sizex = SpriteGetWidth();
	float sizey = SpriteGetHeight();

	float left = position2.x - sizex / 2;
	float right = position2.x + sizex / 2;
	float top = position2.y - sizey / 2;
	float bottom = position2.y + sizey / 2;

	float closestX = std::clamp(position1.x, left, right);
	float closestY = std::clamp(position1.y, top, bottom);

	sf::Vector2f distance = sf::Vector2f(position1.x - closestX, position1.y - closestY);
	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);

	float radius = GetRadius();
	if (sqrLength < (radius * radius))
	{
		std::cout << "Collision Circle -> Rect" << std::endl;
	}
	return sqrLength < (radius * radius);
}


bool Entity::IsInside(float x, float y) const
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	float dx = x - position.x;
	float dy = y - position.y;

	float radius = mSprite.getTexture()->getSize().x * mSprite.getScale().x / 2;
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
	//Utils::Normalize(mDirection);

	float dt = GetDeltaTime();
	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;
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
	if (mAnimatedSpriteType == AnimatedSpriteType::AnimatedSprite)
	{
		UpdateAnimation(dt);
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

void Entity::SetSizeByX(int sizeX)
{
	float ratio = static_cast<float>(sizeX) / mSprite.getTexture()->getSize().x * mAnimation.col;

	SetScale(ratio, ratio);
}

void Entity::SetSizeByY(int sizeY)
{
	float ratio = static_cast<float>(sizeY) / mSprite.getTexture()->getSize().y * mAnimation.row;

	SetScale(ratio, ratio);
}

void Entity::UpdateAnimation(float mDeltaTime)
{
	mAnimation.progress += mDeltaTime;


	if (mAnimation.col != 0) {
		mAnimation.indexX = (mAnimation.indexX + 1) % mAnimation.col;
	}
	else {
		mAnimation.indexX = 0; // or any other appropriate value
	}

	mSprite.setTextureRect(sf::IntRect((GetWidthTexture() / mAnimation.col) * mAnimation.indexX, (GetHeightTexture() / mAnimation.row) * mAnimation.indexY, GetWidthTexture() / mAnimation.row, GetHeightTexture() / mAnimation.col));

	//OnUpdate();

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