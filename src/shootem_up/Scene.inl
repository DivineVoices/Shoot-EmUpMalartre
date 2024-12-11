#pragma once

#include "Scene.h"
#include "GameManager.h"
#include "AssetManager.h"
#include "Entity.h"

template<typename T>
T* Scene::CreateEntity(float _w, const char* _path, AssetManager& assetManager)
{
    static_assert(std::is_base_of<Entity, T>::value, "T must be derived from EntitySFML");

    T* newEntity = new T();

    Entity* entity = newEntity;
    entity->Initialize(_w, _path, assetManager);

    mpGameManager->mEntitiesToAdd.push_back(newEntity);

    return newEntity;
}

template<typename T>
T* Scene::CreateEntity(float _w, float _h, const char* _path, AssetManager& assetManager)
{
    static_assert(std::is_base_of<Entity, T>::value, "T must be derived from EntitySFML");

    T* newEntity = new T();

    Entity* entity = newEntity;
    entity->Initialize(_w, _h, _path, assetManager);

    mpGameManager->mEntitiesToAdd.push_back(newEntity);

    return newEntity;
}