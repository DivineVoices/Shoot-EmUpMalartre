#pragma once

class Entity {

	struct Target
	{
		sf::Vector2i position;
		float distance;
		bool isSet;
	};

public:
	virtual bool GoToDirection(int x, int y, float speed = -1.f) = 0;
	virtual bool GoToPosition(int x, int y, float speed = -1.f) = 0;
	virtual void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f) = 0;
	virtual void SetDirection(float x, float y, float speed = -1.f) = 0;
	virtual void SetSpeed(float speed) = 0;
	virtual void SetTag(int tag) = 0;
	virtual float GetRadius() const = 0;

	virtual bool IsColliding(Entity* other) = 0;

public:
	virtual sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const = 0;
	virtual sf::Shape* GetShape() = 0;

	virtual bool IsTag(int tag) const = 0;
	virtual bool IsInside(float x, float y) const = 0;

	virtual void Destroy() = 0;
	virtual bool ToDestroy() const = 0;

	virtual float GetDeltaTime() const = 0;

protected:
	Entity() = default;
	~Entity() = default;

	virtual void OnUpdate() {};
	virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};

protected:
	sf::CircleShape mShape;
	sf::Vector2f mDirection;
	Target mTarget;
	float mSpeed;
	bool mToDestroy;
	int mTag;

private:
	virtual void Update() = 0;
	virtual void Initialize(float radius, const sf::Color& color) = 0;

	friend class GameManager;
	friend Scene;
};