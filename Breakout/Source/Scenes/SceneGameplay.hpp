#pragma once

#include <Level.hpp>
#include <vector>

#include <ECS/Systems/RenderSystem.hpp>
//#include <ECS/Systems/MovementSystem.hpp>
//#include <ECS/Systems/CollisionSystem.hpp>
#include "Scene.hpp"
#include "ECS/Entities/EntityFactory.hpp"

namespace breakout
{
	class MovementSystem;
	class CollisionSystem;

	class SceneGameplay : public Scene
	{
	public:
		SceneGameplay(MovementSystem &movementSystem, CollisionSystem &collisionSystem, RenderSystem &renderSystem);
		virtual ~SceneGameplay();

		void handleEvent(const SDL_Event& event) override;
		void update(double time) override;
		void render() override;
		
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
		// TODO move somewhere else
		// non-virtual, static?
		void updateHUD(const std::string& tag, const std::string& text);

		int score = 0;
		int lives = 3;

	private:
		//Game &game;

		int currentLevelIndex = 0;
		std::vector<Level*> levels;
		
		// runtime systems
		//RenderSystem renderSystem;
		MovementSystem &movementSystem;
		CollisionSystem &collisionSystem;
	};
}
