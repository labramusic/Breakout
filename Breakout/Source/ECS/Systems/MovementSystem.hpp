#pragma once

#include <SDL_events.h>

#include "System.hpp"

namespace breakout
{
	class SceneGameplay;
	
	class MovementSystem : public System
	{
	public:
		MovementSystem(EntityManager& entityManager, SceneGameplay& scene) : System(entityManager)
		{
			this->scene = &scene;
		}
		MovementSystem() = default;

		void update(double time);
		void onEvent(const SDL_Event& event);
		void resetPositions();

	private:
		bool movingLeft = false;
		bool movingRight = false;

		SceneGameplay* scene;
	};
}
