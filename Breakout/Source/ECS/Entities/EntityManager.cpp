#include "EntityManager.hpp"

#include <iostream>

namespace breakout
{
	EntityManager::EntityManager() : nextId(1) {}

	EntityManager::~EntityManager()
	{
		std::cout << "calling destructor of entity manager" << std::endl;
	}

	Entity *EntityManager::GetEntityByTag(const std::string &tag)
	{
		for (std::unique_ptr<Entity> &entity : entities)
		{
			if (entity && entity->IsActive() && entity->getTag() == tag)
				return entity.get();
		}
		return nullptr;
	}

	void EntityManager::Refresh()
	{
		for (std::unique_ptr<Entity> &entity : entities)
		{
			if (entity && !entity->IsActive())
			{
				removeEntityComponents(*entity);
				entity.reset();
			}
		}
	}

	void EntityManager::removeEntityComponents(Entity &entity)
	{
		for (auto it = componentsByClass.begin(); it != componentsByClass.end(); ++it) {
			auto entityComponent = it->second.find(entity.getId());
			if (entityComponent != it->second.end())
			{
				it->second.erase(entityComponent);
			}
		}
	}

	EntityID EntityManager::generateNewId()
	{
		if (nextId < MAX_ENTITIES)
		{
			return nextId++;
		}

		for (EntityID i = 1; i < MAX_ENTITIES; ++i)
		{
			if (!entities[i])
			{
				return i;
			}
		}

		// no available ids
		return 0;
	}

	Entity &EntityManager::createEntity(const std::string &tag)
	{
		const EntityID id = generateNewId();
		Entity *entity = new Entity(id, tag);
		std::unique_ptr<Entity> uPtr{ entity };
		entities[id] = std::move(uPtr);
		return *entity;
	}
}