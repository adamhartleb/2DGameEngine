#include "Entity.h"

int Entity::getID() const
{
	return m_id;
}

bool Entity::operator==(const Entity& other) const
{
	return m_id == other.m_id;
}