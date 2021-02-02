#pragma once

#include <cstddef>

namespace breakout
{
	using ComponentTypeID = std::size_t;
	constexpr ComponentTypeID MAX_COMPONENTS = 32;
	
	class Component
	{
	public:
		static ComponentTypeID getNewComponentTypeID()
		{
			static ComponentTypeID lastID = 0ull;
			return lastID++;
		}

		// return same id for existing components
		template <typename C>
		static ComponentTypeID getComponentTypeID() noexcept
		{
			static_assert(std::is_base_of<Component, C>::value, "C must inherit from Component.");
			
			static ComponentTypeID typeID = getNewComponentTypeID();
			return typeID;
		}
	};
}