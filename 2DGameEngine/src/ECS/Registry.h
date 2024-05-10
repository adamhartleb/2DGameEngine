#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>

#include "Pool.h"
#include "System.h"

class Registry
{
private:
	int numEntities{0};
	std::vector<BasePool*> componentPools;
	// List of component signatures per entity. Effectively says which components are enabled for the entity.
	std::vector<Signature> entityComponentSignatures;
	std::unordered_map<std::type_index, System*> systems;
public:
	Registry() = default;
};