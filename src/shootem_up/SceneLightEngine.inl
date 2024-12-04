	#pragma once

#include "SceneLightEngine.h"
#include "GameManagerLightEngine.h"
#include "EntityLightEngine.h"

template<typename T>
T* SceneLightEngine::CreateEntity(float radius, const sf::Color& color)
{
	static_assert(std::is_base_of<EntityLightEngine, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	EntityLightEngine* entity = newEntity;
	entity->Initialize(radius, color);
	

	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}
