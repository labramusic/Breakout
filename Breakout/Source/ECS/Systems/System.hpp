#pragma once

namespace breakout
{
	class Game;
	class EntityManager;

	class System
	{
	public:
		virtual ~System() = 0;
		System(const System &) = delete;
		void operator=(const System &) = delete;

	protected:
		explicit System(Game &game);

		Game &game;
		EntityManager &entityManager;
	};
}