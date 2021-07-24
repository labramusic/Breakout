#pragma once

#include <ECS/Entities/EntityManager.hpp>

namespace breakout
{
	class System
	{
	public:
		virtual ~System() = 0;

	protected:
		System(EntityManager& entityManager) : entityManager(entityManager) {}
		//System() = default;

		EntityManager &entityManager;
	};
}