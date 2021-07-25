#pragma once

#include "Scene.hpp"

namespace breakout
{
	class SceneGameOver : public Scene
	{
	public:
		SceneGameOver(const Game &game, RenderSystem &renderSystem);
		virtual ~SceneGameOver();

		void handleEvent(const SDL_Event& event) override;
		void update(double time) override;
		void render() override;

		void loadScene() override;
		void unloadScene() override;
	};
}