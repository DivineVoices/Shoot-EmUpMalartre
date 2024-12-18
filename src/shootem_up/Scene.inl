#pragma once

#include "Scene.h"
#include "GameManager.h"
#include "AssetManager.h"
#include "Entity.h"
#include <iostream>

template<typename T>
T* Scene::CreateEntity(float _w, float _h, std::string _path, int row, int col, float frameTime)
{
    static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

    T* newEntity = new T();

    Entity* entity = newEntity;
    entity->Initialize(_w, _h, _path, row, col, frameTime);

    mpGameManager->mEntitiesToAdd.push_back(newEntity);

    return newEntity;
}