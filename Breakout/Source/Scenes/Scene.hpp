#pragma once
#include <SDL_events.h>

#include <vector>
#include "ECS/Systems/System.hpp"
#include "ECS/Systems/RenderSystem.hpp"

namespace breakout
{
	class Scene
	{
	public:
		Scene(RenderSystem &renderSystem);
		virtual ~Scene();

		virtual void handleEvent(const SDL_Event& event) = 0;
		virtual void update(double time) = 0;
		virtual void render() = 0;
		
		virtual void loadScene() = 0;
		virtual void unloadScene() = 0;

	protected:
		//Game &game;

		RenderSystem &renderSystem;
	};
}
