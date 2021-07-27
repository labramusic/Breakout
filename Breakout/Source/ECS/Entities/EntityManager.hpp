#pragma once

#include <array>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "Entity.hpp"
#include <ECS/Components/Component.hpp>

namespace breakout
{	
	class EntityManager
	{
		friend class EntityFactory;

	public:
		EntityManager();
		~EntityManager();
		EntityManager(const EntityManager&) = delete;
		void operator=(const EntityManager&) = delete;

		Entity *GetEntityByTag(const std::string &tag);
		void Refresh();

		template <typename C>
		C &GetComponent(const Entity &entity)
		{
			static_assert(std::is_base_of<Component, C>::value, "C must inherit from Component.");
			assert(HasComponent<C>(entity));

			Component *p = componentsByClass[Component::GetComponentTypeID<C>()][entity.getId()].get();
			return *static_cast<C*>(p);
		}

		template <typename C>
		bool HasComponent(const Entity &entity)
		{
			static_assert(std::is_base_of<Component, C>::value, "C must inherit from Component.");

			ComponentTypeID cId = Component::GetComponentTypeID<C>();
			if (componentsByClass.find(cId) != componentsByClass.end())
			{
				return componentsByClass[cId].find(entity.getId()) != componentsByClass[cId].end();
			}
			return false;
		}
				
		template <typename C>
		std::vector<Entity*> GetEntitiesWithComponent()
		{
			static_assert(std::is_base_of<Component, C>::value, "C must inherit from Component.");

			std::vector<Entity*> entitiesWithComponent;
			ComponentTypeID cId = Component::GetComponentTypeID<C>();
			if (componentsByClass.find(cId) != componentsByClass.end())
			{
				for (auto it = componentsByClass[cId].begin(); it != componentsByClass[cId].end(); ++it)
				{
					Entity &e = *entities[it->first];
					if (!e.IsActive()) continue;
					entitiesWithComponent.push_back(&e);
				}
			}
			
			return entitiesWithComponent;
		}

	private:
		std::array<std::unique_ptr<Entity>, MAX_ENTITIES> entities;
		std::unordered_map<ComponentTypeID, std::unordered_map<EntityID, std::unique_ptr<Component>>> componentsByClass;
		EntityID nextId;

		EntityID generateNewId();
		Entity &createEntity(const std::string &tag = "");
		void removeEntityComponents(Entity &entity);

		template <typename C, typename... CArgs>
		C& addComponent(Entity &entity, CArgs&&... cArgs)
		{
			static_assert(std::is_base_of<Component, C>::value, "C must inherit from Component.");
			assert(!HasComponent<C>(entity));

			ComponentTypeID cId = Component::GetComponentTypeID<C>();
			if (componentsByClass.find(cId) == componentsByClass.end())
			{
				componentsByClass[cId] = std::unordered_map<EntityID, std::unique_ptr<Component>>{};
			}

			C *component(new C(std::forward<CArgs>(cArgs)...));

			std::unique_ptr<Component> uPtr{ component };
			componentsByClass[cId][entity.getId()] = std::move(uPtr);

			return *component;
		}
	};
}
