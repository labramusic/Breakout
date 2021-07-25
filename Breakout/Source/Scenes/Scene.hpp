#pragma once
#include <SDL_events.h>

namespace breakout
{
	class Game;
	class SceneManager;
	class RenderSystem;

	class Scene
	{
	public:
		Scene(const Game &game, RenderSystem &renderSystem);
		virtual ~Scene();

		virtual void handleEvent(const SDL_Event& event);
		virtual void update(double time) = 0;
		virtual void render() = 0;
		
		virtual void loadScene() = 0;
		virtual void unloadScene() = 0;

	protected:
		const Game &game;

		RenderSystem &renderSystem;
	};
}
