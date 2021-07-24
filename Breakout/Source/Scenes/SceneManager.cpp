#include "SceneManager.hpp"

#include "Game.hpp"
#include "ECS/Systems/MovementSystem.hpp"
#include "ECS/Systems/CollisionSystem.hpp"

namespace breakout
{
	SceneManager::SceneManager()
	{
		//Scene* main = new SceneMain();
		//Scene* gameOver = new SceneGameOver();
		//Scene *gameplay = new SceneGameplay();
		//addScene(Gameplay, *gameplay);

		// initialize systems
		RenderSystem * renderSystem = new RenderSystem(Game::instance().getEntityManager());
		MovementSystem* movementSystem = new MovementSystem(Game::instance().getEntityManager());
		CollisionSystem* collisionSystem = new CollisionSystem(Game::instance().getEntityManager());
		// store systems for deallocation
		systems.push_back(renderSystem);
		systems.push_back(movementSystem);
		systems.push_back(collisionSystem);

		scenes.emplace(Main, new SceneMain(*renderSystem));
		SceneGameplay* gameplayScene = new SceneGameplay(*movementSystem, *collisionSystem, *renderSystem);
		scenes.emplace(Gameplay, gameplayScene);

		movementSystem->setScene(*gameplayScene);
		collisionSystem->setScene(*gameplayScene);

		// start with main scene
		activeScene = scenes[Main];
		activeScene->loadScene();
	}
}