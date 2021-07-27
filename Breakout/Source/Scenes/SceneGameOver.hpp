#pragma once

#include "Scene.hpp"

namespace breakout
{
	class SceneGameOver : public Scene
	{
	public:
		SceneGameOver(Game &game, RenderSystem &renderSystem);
		virtual ~SceneGameOver();

		void HandleEvent(const SDL_Event& event) override;
		void Update(double time) override;
		void Render() override;

		void LoadScene() override;
		void UnloadScene() override;
	};
}