#include "System.h"

#include <algorithm>
#include <functional>

void System::addEntity(Entity entity)
{
	m_entities.push_back(entity);
}

void System::removeEntity(const Entity& entity)
{
	std::erase_if(m_entities, [&](const Entity& other) {
		return entity == other;
	});
}