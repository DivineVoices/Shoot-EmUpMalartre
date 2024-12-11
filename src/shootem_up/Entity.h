#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>


namespace sf 
{
	class Shape;
    class Color;
}

class Scene;
class Collider;
class AssetManager;

class Entity
{
    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

    enum class CollisionType
    {
        Circle,
        AABB
    };

protected:
    sf::Texture mTexture;
    sf::Sprite mSprite;
    sf::CircleShape mShape;
    sf::Vector2f mDirection;
    Target mTarget;
    CollisionType mCollisionType;
    float mSpeed;
    bool mToDestroy;
    int mTag;
    int mFrameWidth;
    int mFrameHeight;
    int mNumFrames;
    float mFrameTime;
    int mCurrentFrame;
    float mElapsedTime;

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
    bool IsColliding(Entity* other) const;

	void Destroy() { mToDestroy = true; }
	bool ToDestroy() const { return mToDestroy; }
	
	template<typename T>
	T* GetScene() const;

    Scene* GetScene() const;
	float GetDeltaTime() const;

    void SetScale(float _scaleX, float _scaleY) { mSprite.setScale(_scaleX, _scaleY); }
    void SetSizeWH(float _w, float _h) { SetScale(_w / GetTexture().getSize().x, _h / GetTexture().getSize().y); }
    float SpriteGetWidth() const { return mSprite.getTexture()->getSize().x * mSprite.getScale().x; }
    float SpriteGetHeight() const { return mSprite.getTexture()->getSize().y * mSprite.getScale().y; }
    sf::Texture& GetTexture() { return mTexture; }
    sf::Sprite& GetSprite() { return mSprite; }

    void DrawCollision(sf::RenderWindow* window) const;

    template<typename T>
    T* CreateEntity(float _w, const char* _path, AssetManager& assetManager);

    template<typename T>
    T* CreateEntity(float _w, float _h, const char* _path, AssetManager& assetManager);

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	
private:
    void Update();
    void Initialize(float _w, const char* _path, AssetManager& assetManager);
    void Initialize(float _w, float _h, const char* _path, AssetManager& assetManager);

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"