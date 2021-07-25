#include "SceneMain.hpp"

#include <Game.hpp>
#include <ECS/Entities/EntityFactory.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Systems/RenderSystem.hpp>

#include "SceneManager.hpp"

namespace breakout
{
	SceneMain::SceneMain(const Game &game, RenderSystem &renderSystem) : Scene(game, renderSystem)
	{
	}

	SceneMain::~SceneMain()
	{
	}

	void SceneMain::handleEvent(const SDL_Event& event)
	{
		Scene::handleEvent(event);

		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				// start game
				game.getSceneManager().changeScene(SceneManager::SceneName::Gameplay);
			}
		}
	}

	void SceneMain::update(double time)
	{
	}

	void SceneMain::render()
	{
		// TODO once?
		//Game::instance().getAssetManager().DrawBackground(levels[currentLevelIndex]->levelId);

		renderSystem.update();
	}

	void SceneMain::loadScene()
	{
		//Game::instance().getAssetManager().DrawBackground(levels[currentLevelIndex]->levelId);

		SDL_Color white = { 255, 255, 255, 255 };
		game.getEntityFactory().createLabel("gameTitle", 350, 200, "BREAKOUT", white);
		game.getEntityFactory().createLabel("playMsg", 320, 250, "Press Space to play", white);
	}

	void SceneMain::unloadScene()
	{
		game.getEntityFactory().destroyEntitiesWithComponent<TransformComponent>();
	}
}