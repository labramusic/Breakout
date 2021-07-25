#pragma once

#include "System.hpp"
#include <SDL_events.h>

namespace breakout
{
	class EntityManager;
	class SceneGameplay;
	
	class MovementSystem : public System
	{
	public:
		explicit MovementSystem(const Game &game);
		virtual ~MovementSystem();

		void update(double time);
		void onEvent(const SDL_Event& event);
		void resetPositions();

		void setScene(SceneGameplay &scene) { gameplayScene = &scene; }

	private:
		SceneGameplay* gameplayScene;

		bool movingLeft = false;
		bool movingRight = false;
	};
}
