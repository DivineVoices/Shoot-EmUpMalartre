#include "pch.h"

#include "DummyEntity.h"

#include <iostream>

void DummyEntity::OnCollisionCircleCircle(Entity* other)
{
	std::cout << "DummyEntity::OnCollisionCircleCircle" << std::endl;
}

void DummyEntity::OnCollisionRectRect(Entity* other)
{
	std::cout << "DummyEntity::OnCollisionRectRect" << std::endl;
}

void DummyEntity::OnCollisionCircleRect(Entity* other)
{
	std::cout << "DummyEntity::OnCollisionCircleRect" << std::endl;
}