#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>


namespace sf 
{
	class Shape;
    class Color;
}

class Scene;
class Collider;

class Entity
{
    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

protected:
    sf::CircleShape mShape;
    sf::Vector2f mDirection;
    Collider* mCollider;
	Target mTarget;
    float mSpeed;
    bool mToDestroy;
    int mTag;

public:
	bool GoToDirection(int x, int y, float speed = -1.f);
    bool GoToPosition(int x, int y, float speed = -1.f);
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	void SetDirection(float x, float y, float speed = -1.f);
    void SetSize(float x, float y);
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetTag(int tag) { mTag = tag; }
	float GetRadius() const { return mShape.getRadius(); }

    sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;
	sf::Shape* GetShape() { return &mShape; }

	bool IsTag(int tag) const { return mTag == tag; }
    bool IsCollidingCircleCircle(Entity* other) const;
    bool IsCollidingRectRect(Entity* other) const;
    bool IsCollidingCircleRect(Entity* other) const;
	bool IsInside(float x, float y) const;

	void Destroy() { mToDestroy = true; }
	bool ToDestroy() const { return mToDestroy; }
	
	template<typename T>
	T* GetScene() const;

    Scene* GetScene() const;
	float GetDeltaTime() const;

    template<typename T>
    T* CreateEntity(float radius, const sf::Color& color);

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnUpdate() {};
    virtual void OnCollisionCircleCircle(Entity* collidedWith) {};
    virtual void OnCollisionRectRect(Entity* collidedWith) {};
    virtual void OnCollisionCircleRect(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	
private:
    void Update();
	void Initialize(float radius, const sf::Color& color);

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"