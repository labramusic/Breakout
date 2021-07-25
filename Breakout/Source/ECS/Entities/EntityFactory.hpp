#pragma once

#include "EntityManager.hpp"
#include <SDL.h>
#include <SDL_pixels.h>
#include <cassert>

namespace breakout
{
	class Game;
	class BrickType;

	class EntityFactory
	{
	public:
		explicit EntityFactory(const Game &game);

		Entity& createPaddle() const;
		Entity& createBall() const;
		Entity& createBrick(const BrickType& brickType, float x, float y, float w, float h) const;
		Entity& createLabel(const std::string& tag, float x, float y, const std::string& text, SDL_Color color) const;

		template <typename C>
		void destroyEntitiesWithComponent()
		{
			static_assert(std::is_base_of<Component, C>::value, "C must inherit from Component.");
			for (auto const& entity : manager.getEntitiesWithComponent<C>())
			{
				manager.removeEntity(*entity);
			}
			manager.refresh();
		}

	private:
		const Game &game;
		EntityManager &manager;
	};
}