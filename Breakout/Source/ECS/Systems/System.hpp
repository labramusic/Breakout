#pragma once

#include <ECS/Entities/EntityManager.hpp>

namespace breakout
{
	class System
	{
	public:
		System(EntityManager& entityManager) : entityManager(&entityManager) {}
		System() = default;

	protected:
		EntityManager* entityManager;
	};
}