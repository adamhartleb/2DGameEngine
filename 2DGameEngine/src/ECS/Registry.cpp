#include "Registry.h"
#include "../Logger/Logger.h"

Entity Registry::createEntity()
{
	int entityID{ numEntities++ };

	Entity entity{ entityID };
	entitiesToBeAdded.insert(entity);

	Logger::Log("Entity created with id = " + std::to_string(entityID));

	return entity;
}

void Registry::update()
{

}