#pragma once

#include <vector>
#include <string>
#include <memory>

#include "Scene.hpp"

namespace breakout
{
	class Level;
	class EntityManager;
	class MovementSystem;
	class CollisionSystem;

	class SceneGameplay : public Scene
	{
	public:
		SceneGameplay(Game &game, MovementSystem &movementSystem, CollisionSystem &collisionSystem, RenderSystem &renderSystem);
		virtual ~SceneGameplay();

		void HandleEvent(const SDL_Event &event) override;
		void Update(double time) override;
		void Render() override;
		
		void LoadScene() override;
		void UnloadScene() override;

		void LoseLife();
		void AddScore(int points);

	private:
		EntityManager &entityManager;
		
		// runtime systems
		MovementSystem &movementSystem;
		CollisionSystem &collisionSystem;

		int currentLevelIndex = 0;
		std::vector<std::unique_ptr<Level>> levels;
		
		bool isGameOver;
		int score = 0;
		int lives = 3;

		void loadLevel();
		void unloadLevel() const;
		
		bool levelFinished() const;
		void nextLevel();
		void gameOver();

		void updateHUD(const std::string &tag, const std::string &text) const;
	};
}
