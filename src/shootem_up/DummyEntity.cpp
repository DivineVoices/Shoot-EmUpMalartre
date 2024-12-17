#include "pch.h"

#include "DummyEntity.h"

#include <iostream>

void DummyEntity::OnCollision(Entity* other)
{
	std::cout << "DummyEntity::OnCollision" << std::endl;
}

void DummyEntity::OnUpdate()
{
	/*std::cout << hp << std::endl;
	hp -= 1;*/
	if (hp <= 0) {
		Destroy();
	}
}
