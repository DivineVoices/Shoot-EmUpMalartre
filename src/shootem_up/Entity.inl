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
T* Entity::CreateEntity(float _w, float _h, std::string _path, int row, int col, float frameTime)
{
	return GetScene()->CreateEntity<T>(_w, _h, _path, row, col, frameTime);
}
