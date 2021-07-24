#pragma once

#include "Scene.hpp"

namespace breakout 
{
	class SceneMain : public Scene
	{
	public:
		SceneMain(RenderSystem &renderSystem);
		virtual ~SceneMain();

		void handleEvent(const SDL_Event& event) override;
		void update(double time) override;
		void render() override;

		void loadScene() override;
		void unloadScene() override;

	private:
		//Game &game;

		// renderSystem
	};
}