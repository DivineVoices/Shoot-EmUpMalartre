#include "Entity.h"

#include "GameManager.h"

template<typename T>
T* Entity::GetScene() const
{
	T* pScene = dynamic_cast<T*>(GetScene());

	_ASSERT(pScene != nullptr);

	return pScene;
}


template<typename T>
T* Entity::CreateEntity(float _w, const char* _path, AssetManager& assetManager)
{
	Scene* pScene = GetScene<Scene>();
	_ASSERT(pScene != nullptr);
	return GetScene()->CreateEntity<T>(_w, _path, assetManager);
}

template<typename T>
T* Entity::CreateEntity(float _w, float _h, const char* _path, AssetManager& assetManager)
{
	Scene* pScene = GetScene<Scene>();
	_ASSERT(pScene != nullptr);
	return pScene->CreateEntity<T>(_w, _h, _path, assetManager);
}

//template<typename T>
//T* Entity::CreateAnimatedEntity(float _w, float _h, const char* _path, int frameWidth, int frameHeight, int numFrames, float frameTime, AssetManager& assetManager)
//{
//	SceneSFML* pScene = GetScene<SceneSFML>();
//	_ASSERT(pScene != nullptr);
//	return pScene->CreateAnimatedEntity<T>(_w, _h, _path, frameWidth, frameHeight, numFrames, frameTime, assetManager);
//}