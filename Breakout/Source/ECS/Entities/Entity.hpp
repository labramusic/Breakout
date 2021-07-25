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
		Entity(EntityID id, std::string tag) : id(id), tag(std::move(tag)) {}

		~Entity()
		{
			std::cout << "destroying entity " << id << std::endl;
		}

		EntityID getId() const { return id; }
		std::string getTag() const { return tag; }

		bool active = true;
		
	private:
		EntityID id;
		std::string tag;
	};
}