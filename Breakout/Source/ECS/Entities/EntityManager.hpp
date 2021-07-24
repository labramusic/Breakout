#pragma once

#include <array>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "Entity.hpp"
#include <ECS/Components/Component.hpp>
//#include "EntityFactory.hpp"

#include <iostream>

namespace breakout
{	
	class EntityManager
	{
		friend class EntityFactory;

	public:
		EntityManager() : nextId(1) {}

		~EntityManager()
		{
			std::cout << "calling destructor of entity manager" << std::endl;

			for (auto& entity : entities)
			{
				if (!entity) continue;
				for (auto it = componentsByClass.begin(); it != componentsByClass.end(); ++it) {
					auto entityComponent = it->second.find(entity->getId());
					if (entityComponent != it->second.end())
					{
						it->second.erase(entityComponent);
					}
				}

				entities[entity->getId()].reset();
			}
		}

		Entity* getEntityByTag(const std::string& tag)
		{
			for (auto& entity : entities)
			{
				if (entity && entity->getTag() == tag)
					return entity.get();
			}
			return nullptr;
		}

		void removeEntity(Entity& entity)
		{
			for (auto it = componentsByClass.begin(); it != componentsByClass.end(); ++it) {
				auto entityComponent = it->second.find(entity.getId());
				if (entityComponent != it->second.end())
				{
					it->second.erase(entityComponent);
				}
			}

			entities[entity.getId()]->active = false;
		}

		template <typename C>
		C& getComponent(const Entity& entity)
		{
			static_assert(std::is_base_of<Component, C>::value, "C must inherit from Component.");
			assert(hasComponent<C>(entity));

			Component* p = componentsByClass[Component::getComponentTypeID<C>()][entity.getId()].get();
			return *static_cast<C*>(p);
		}

		template <typename C>
		bool hasComponent(const Entity& entity)
		{
			auto cId = Component::getComponentTypeID<C>();
			if (componentsByClass.find(cId) != componentsByClass.end())
			{
				return componentsByClass[cId].find(entity.getId()) != componentsByClass[cId].end();
			}
			return false;
		}
				
		template <typename C>
		std::vector<Entity*> getEntitiesWithComponent()
		{
			static_assert(std::is_base_of<Component, C>::value, "C must inherit from Component.");

			std::vector<Entity*> entitiesWithComponent;
			auto cId = Component::getComponentTypeID<C>();
			if (componentsByClass.find(cId) != componentsByClass.end())
			{
				for (auto it = componentsByClass[cId].begin(); it != componentsByClass[cId].end(); ++it)
				{
					entitiesWithComponent.push_back(entities[it->first].get());
				}
			}
			
			return entitiesWithComponent;
		}

		void refresh()
		{
			for (auto& entity : entities)
			{
				if (entity && !entity->active) entity.reset();
			}
		}

	private:
		std::array<std::unique_ptr<Entity>, MAX_ENTITIES> entities;
		std::unordered_map<ComponentTypeID, std::unordered_map<EntityID, std::unique_ptr<Component>>> componentsByClass;
		EntityID nextId;

		EntityID generateNewId()
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

		Entity& createEntity(const std::string& tag = "")
		{
			const EntityID id = generateNewId();
			Entity* entity = new Entity(id, tag);
			std::unique_ptr<Entity> uPtr{ entity };
			entities[id] = std::move(uPtr);
			return *entity;
		}

		template <typename C, typename... CArgs>
		C& addComponent(Entity& entity, CArgs&&... cArgs)
		{
			static_assert(std::is_base_of<Component, C>::value, "C must inherit from Component.");
			assert(!hasComponent<C>(entity));

			auto cId = Component::getComponentTypeID<C>();
			if (componentsByClass.find(cId) == componentsByClass.end())
			{
				componentsByClass[cId] = std::unordered_map<EntityID, std::unique_ptr<Component>>{};
			}

			C* component(new C(std::forward<CArgs>(cArgs)...));

			std::unique_ptr<Component> uPtr{ component };
			componentsByClass[cId][entity.getId()] = std::move(uPtr);

			return *component;
		}
	};
}
