#include "SceneManager.hpp"

#include "Scene.hpp"
#include "SceneGameplay.hpp"
#include "SceneMain.hpp"
#include "SceneGameOver.hpp"

#include <Game.hpp>
#include <ECS/Systems/RenderSystem.hpp>
#include <ECS/Systems/MovementSystem.hpp>
#include <ECS/Systems/CollisionSystem.hpp>

#include <iostream>

namespace breakout
{
	SceneManager::SceneManager(const Game &game) : game(game)
	{
		// initialize systems
		RenderSystem * renderSystem = new RenderSystem(game);
		MovementSystem* movementSystem = new MovementSystem(game);
		CollisionSystem* collisionSystem = new CollisionSystem(game);
		// store systems for deallocation
		systems.push_back(renderSystem);
		systems.push_back(movementSystem);
		systems.push_back(collisionSystem);

		scenes.emplace(Main, new SceneMain(game, *renderSystem));
		SceneGameplay* gameplayScene = new SceneGameplay(game, *movementSystem, *collisionSystem, *renderSystem);
		scenes.emplace(Gameplay, gameplayScene);
		scenes.emplace(GameOver, new SceneGameOver(game, *renderSystem));

		movementSystem->setScene(*gameplayScene);
		collisionSystem->setScene(*gameplayScene);

		// start with main scene
		activeScene = scenes[Main];
		activeScene->loadScene();
	}

	SceneManager::~SceneManager()
	{
		std::cout << "calling destructor of scene manager" << std::endl;

		for (auto it = systems.begin(); it != systems.end(); ++it) {
			delete* it;
		}

		for (auto it = scenes.begin(); it != scenes.end(); ++it) {
			delete it->second;
		}
	}

	void SceneManager::update(double time)
	{
		activeScene->update(time);
	}

	void SceneManager::render()
	{
		activeScene->render();
	}

	void SceneManager::handleEvent(const SDL_Event& event)
	{
		activeScene->handleEvent(event);
	}

	void SceneManager::changeScene(const SceneName newScene)
	{
		activeScene->unloadScene();
		activeScene = scenes[newScene];
		activeScene->loadScene();
	}
}