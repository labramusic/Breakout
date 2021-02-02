#pragma once

#include "EntityManager.hpp"
#include <BrickType.hpp>
#include <SDL_pixels.h>

namespace breakout
{
	class EntityFactory
	{
	public:
		EntityFactory(): manager(nullptr)
		{
		}

		explicit EntityFactory(EntityManager& manager) : manager(&manager) {}

		Entity& createPaddle() const;
		Entity& createBall() const;
		Entity& createBrick(const BrickType& brickType, float x, float y, float w, float h) const;
		Entity& createLabel(const std::string& tag, float x, float y, const std::string& text, SDL_Color color) const;

	private:
		EntityManager* manager;
	};
}
