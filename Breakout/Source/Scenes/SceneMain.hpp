#pragma once

#include "Scene.hpp"

namespace breakout 
{
	class SceneMain : public Scene
	{
	public:
		SceneMain(Game &game, RenderSystem &renderSystem);
		virtual ~SceneMain();

		void HandleEvent(const SDL_Event& event) override;
		void Update(double time) override;
		void Render() override;

		void LoadScene() override;
		void UnloadScene() override;
	};
}