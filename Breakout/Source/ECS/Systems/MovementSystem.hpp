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
		explicit MovementSystem(Game &game);
		virtual ~MovementSystem();
		MovementSystem(const MovementSystem&) = delete;
		void operator=(const MovementSystem&) = delete;

		void OnEvent(const SDL_Event &event);
		void Update(double time) const;

		void ResetPositions() const;

		void SetScene(SceneGameplay &scene) { gameplayScene = &scene; }

	private:
		SceneGameplay* gameplayScene;

		bool movingLeft = false;
		bool movingRight = false;
	};
}
