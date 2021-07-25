#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Scene.hpp"

namespace breakout
{
	class Level;
	class MovementSystem;
	class CollisionSystem;

	class SceneGameplay : public Scene
	{
	public:
		SceneGameplay(const Game &game, MovementSystem &movementSystem, CollisionSystem &collisionSystem, RenderSystem &renderSystem);
		virtual ~SceneGameplay();

		void handleEvent(const SDL_Event &event) override;
		void update(double time) override;
		void render() override;
		
		void loadScene() override;
		void unloadScene() override;

		void loadLevel();
		void unloadLevel();

		void nextLevel();
		void gameOver();

		void updateHUD(const std::string& tag, const std::string& text);

		int score = 0;
		int lives = 3;

	private:
		int currentLevelIndex = 0;
		std::vector<std::unique_ptr<Level>> levels;
		
		// runtime systems
		MovementSystem &movementSystem;
		CollisionSystem &collisionSystem;
	};
}
