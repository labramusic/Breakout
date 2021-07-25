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
		explicit System(const Game &game);

		const Game &game;
		EntityManager &entityManager;
	};
}