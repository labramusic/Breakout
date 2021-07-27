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
		explicit EntityFactory(Game &game);
		EntityFactory(const EntityFactory&) = delete;
		void operator=(const EntityFactory&) = delete;

		Entity &CreatePaddle() const;
		Entity &CreateBall() const;
		Entity &CreateBrick(const BrickType &brickType, float x, float y, float w, float h) const;
		Entity &CreateLabel(const std::string &tag, float x, float y, const std::string &text, SDL_Color color) const;

		template <typename C>
		void destroyEntitiesWithComponent()
		{
			static_assert(std::is_base_of<Component, C>::value, "C must inherit from Component.");
			for (Entity* const &entity : manager.GetEntitiesWithComponent<C>())
			{
				entity->SetActive(false);
			}
			manager.Refresh();
		}

	private:
		Game &game;
		EntityManager &manager;
	};
}