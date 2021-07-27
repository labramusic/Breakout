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
		virtual ~Scene();

		virtual void HandleEvent(const SDL_Event& event);
		virtual void Update(double time) = 0;
		virtual void Render() = 0;
		
		virtual void LoadScene() = 0;
		virtual void UnloadScene() = 0;

	protected:
		Scene(Game &game, RenderSystem &renderSystem);

		Game &game;
		RenderSystem &renderSystem;
	};
}
