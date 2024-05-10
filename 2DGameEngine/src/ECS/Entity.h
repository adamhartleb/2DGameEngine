#pragma once

class Entity
{
private:
	int m_id;
public:
	Entity(int id) : m_id{ id } {}
	int getID() const;
	bool operator==(const Entity& other) const;
};