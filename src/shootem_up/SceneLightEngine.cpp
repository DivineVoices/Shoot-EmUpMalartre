#include "pch.h"

#include "SceneLightEngine.h"

#include "GameManagerLightEngine.h"

int SceneLightEngine::GetWindowWidth() const
{
	return mpGameManager->mWindowWidth;
}

int SceneLightEngine::GetWindowHeight() const
{
	return mpGameManager->mWindowHeight;
}

float SceneLightEngine::GetDeltaTime() const
{
	return mpGameManager->mDeltaTime;
}
