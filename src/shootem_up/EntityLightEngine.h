#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Entity.h"

namespace sf 
{
	class Shape;
    class Color;
}

class Scene;

class EntityLightEngine : public Entity
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
	Target mTarget;
    float mSpeed;
    bool mToDestroy;
    int mTag;

public:
	bool GoToDirection(int x, int y, float speed = -1.f) override;
    bool GoToPosition(int x, int y, float speed = -1.f) override;
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f) override;
	void SetDirection(float x, float y, float speed = -1.f) override;
	void SetSpeed(float speed) override { mSpeed = speed; }
	void SetTag(int tag) override { mTag = tag; }
	float GetRadius() const override{ return mShape.getRadius(); }

    sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;
	sf::Shape* GetShape() { return &mShape; }

	bool IsTag(int tag) const { return mTag == tag; }
    bool IsColliding(Entity* other) override;
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
    EntityLightEngine() = default;
    ~EntityLightEngine() = default;

    virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	
private:
    void Update();
	void Initialize(float radius, const sf::Color& color);

    friend class GameManager;
    friend Scene;
};

#include "EntityLightEngine.inl"