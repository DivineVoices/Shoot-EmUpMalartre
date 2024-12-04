#pragma once

#include "GameManagerLightEngine.h"
#include "SceneLightEngine.h"

template<typename T>
void GameManagerLightEngine::LaunchScene()
{
	static_assert(std::is_base_of<SceneLightEngine, T>::value, "T must be derived from Scene");
	_ASSERT(mpScene == nullptr);

	T* newScene = new T();
	mpScene = newScene;

	mpScene->SetGameManager(this);
	mpScene->OnInitialize();

	Run();
}
