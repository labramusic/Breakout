#pragma once

#include <utility>
#include <memory>
#include <algorithm>
#include <cstddef>

#include <iostream>

namespace breakout
{	
	using EntityID = std::size_t;
	constexpr EntityID MAX_ENTITIES = 1000;
	
	class Entity
	{
	public:		
		Entity(EntityID id, std::string tag) : id(id), tag(std::move(tag)), active(true) {}

		~Entity()
		{
			std::cout << "destroying entity " << id << std::endl;
		}

		EntityID getId() const { return id; }
		std::string getTag() const { return tag; }
		int IsActive() const { return active; }
		void SetActive(bool active) { this->active = active; }
		
	private:
		EntityID id;
		std::string tag;
		bool active;
	};
}