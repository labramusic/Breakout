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
		RenderSystem *renderSystem = new RenderSystem(game);
		MovementSystem *movementSystem = new MovementSystem(game);
		CollisionSystem *collisionSystem = new CollisionSystem(game);

		// store systems for deallocation
		std::unique_ptr<System> rs(renderSystem);
		std::unique_ptr<System> ms(movementSystem);
		std::unique_ptr<System> cs(collisionSystem);
		systems.push_back(std::move(rs));
		systems.push_back(std::move(ms));
		systems.push_back(std::move(cs));

		scenes.emplace(SceneName::Main, new SceneMain(game, *renderSystem));
		SceneGameplay* gameplayScene = new SceneGameplay(game, *movementSystem, *collisionSystem, *renderSystem);
		scenes.emplace(SceneName::Gameplay, gameplayScene);
		scenes.emplace(SceneName::GameOver, new SceneGameOver(game, *renderSystem));

		movementSystem->setScene(*gameplayScene);
		collisionSystem->setScene(*gameplayScene);

		// set main scene as active
		activeScene = scenes[SceneName::Main].get();
		activeScene->loadScene();
	}

	SceneManager::~SceneManager()
	{
		std::cout << "calling destructor of scene manager" << std::endl;
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
		activeScene = scenes[newScene].get();
		activeScene->loadScene();
	}
}