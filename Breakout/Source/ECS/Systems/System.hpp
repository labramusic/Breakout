#pragma once

namespace breakout
{
	class Game;
	class EntityManager;

	class System
	{
	public:
		virtual ~System() = 0;

	protected:
		System(const Game &game);
		//System() = default;

		const Game &game;
		EntityManager &entityManager;
	};
}