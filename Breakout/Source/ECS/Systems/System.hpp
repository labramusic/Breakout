#pragma once

namespace breakout
{
	class EntityManager;

	class System
	{
	public:
		virtual ~System() = 0;

	protected:
		System(EntityManager& entityManager);
		//System() = default;

		EntityManager &entityManager;
	};
}