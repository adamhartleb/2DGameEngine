#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

#include "Pool.h"
#include "System.h"
#include "Entity.h"
#include "Component.h"

class Registry
{
private:
	int numEntities{0};
	std::vector<BasePool*> componentPools;
	// List of component signatures per entity. Effectively says which components are enabled for the entity.
	std::vector<Signature> entityComponentSignatures;
	std::unordered_map<std::type_index, System*> systems;

	std::set<Entity> entitiesToBeAdded;
	std::set<Entity> entitiesToBeKilled;
public:
	Registry() = default;

	void addEntityToSystem(Entity entity);
	Entity createEntity();
	void update();
	
	template <typename T, typename ...TArgs>
	void addComponent(Entity entity, TArgs&& ...args)
	{
		const auto componentID{ Component<T>::getID() };
		const auto entityID{ entity.getID() };

		if (componentID >= componentPools.size())
		{
			componentPools.resize(componentID + 1, nullptr);
		}

		if (!componentPools[componentID])
		{
			Pool<T>* newComponentPool {new Pool<T>()};
			componentPools[componentID] = newComponentPool;
		}

		Pool<T>* componentPool = componentPools[componentID];
	}
};