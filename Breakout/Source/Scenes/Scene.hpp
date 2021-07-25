#pragma once
#include <SDL_events.h>

namespace breakout
{
	class RenderSystem;

	class Scene
	{
	public:
		Scene(RenderSystem &renderSystem);
		virtual ~Scene();

		virtual void handleEvent(const SDL_Event& event);
		virtual void update(double time) = 0;
		virtual void render() = 0;
		
		virtual void loadScene() = 0;
		virtual void unloadScene() = 0;

	protected:
		//Game &game;

		RenderSystem &renderSystem;
	};
}
