#pragma once

#include <Level.hpp>
#include <vector>

#include <ECS/Systems/RenderSystem.hpp>
#include <ECS/Systems/MovementSystem.hpp>
#include <ECS/Systems/CollisionSystem.hpp>
#include "Scene.hpp"
#include "ECS/Entities/EntityFactory.hpp"

namespace breakout
{
	class SceneGameplay : public Scene
	{
	public:
		SceneGameplay();

		void update(double time) override;
		void render() override;
		void handleEvent(const SDL_Event& event) override;
		
		void loadScene() override;
		void unloadScene() override;

		void loadLevel();
		void unloadLevel();

		void addLevel(Level& level)
		{
			levels.push_back(&level);
		}

		void nextLevel();
		void gameOver();
		void updateHUD(const std::string& tag, const std::string& text);

		int score = 0;
		int lives = 3;

	private:
		int currentLevelIndex = 0;
		std::vector<Level*> levels;

		EntityFactory entityFactory;
		
		// systems
		RenderSystem renderSystem;
		MovementSystem movementSystem;
		CollisionSystem collisionSystem;
	};
}
