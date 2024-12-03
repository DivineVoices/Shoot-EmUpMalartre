#include "EntityLightEngine.h"

#include "GameManagerLightEngine.h"

template<typename T>
T* EntityLightEngine::GetScene() const
{
	T* pScene = dynamic_cast<T*>(GetScene());

	_ASSERT(pScene != nullptr);

	return pScene;
}


template<typename T>
T* EntityLightEngine::CreateEntity(float radius, const sf::Color& color)
{
	return GetScene()->CreateEntity<T>(radius, color);
}