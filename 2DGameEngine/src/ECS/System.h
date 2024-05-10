#pragma once

#include <vector>
#include <bitset>

#include "Entity.h"
#include "Component.h"

constexpr unsigned int MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

class System
{
private:
	Signature m_componentSignature;
	std::vector<Entity> m_entities;
public:
	System() = default;
	~System() = default;
	void addEntity(Entity entity);
	void removeEntity(const Entity& entity);
	const std::vector<Entity>& getEntities() const { return m_entities; };
	const Signature& getComponentSignature() const { return m_componentSignature; };

	// Defines the component type that entities must have to be considered by the system.
	template<typename TComponent> void requireComponent();

};

template<typename TComponent> void System::requireComponent()
{
	const auto componentID = Component<TComponent>::getID();
	m_componentSignature.set(componentID);
}