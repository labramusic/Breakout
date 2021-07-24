#pragma once

#include <SDL_events.h>
#include "System.hpp"
#include "Scenes/SceneGameplay.hpp"

union SDL_Event;

namespace breakout
{
	class System;
	class EntityManager;
	class SceneGameplay;
	
	class MovementSystem : public System
	{
	public:
		MovementSystem(EntityManager& entityManager) : System(entityManager), gameplayScene(nullptr)
		{
		}
		//MovementSystem() = default;
		virtual ~MovementSystem() {}

		void update(double time);
		void onEvent(const SDL_Event& event);
		void resetPositions();

		void setScene(SceneGameplay &scene) { gameplayScene = &scene; }

	private:
		bool movingLeft = false;
		bool movingRight = false;

		SceneGameplay* gameplayScene;
	};
}
