#include "SceneGameOver.hpp"

#include <Game.hpp>
#include <ECS/Entities/EntityFactory.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Systems/RenderSystem.hpp>

#include "SceneManager.hpp"

namespace breakout
{
	SceneGameOver::SceneGameOver(const Game &game, RenderSystem& renderSystem) : Scene(game, renderSystem)
	{
	}

	SceneGameOver::~SceneGameOver()
	{
	}

	void SceneGameOver::handleEvent(const SDL_Event& event)
	{
		Scene::handleEvent(event);

		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				// restart game
				game.getSceneManager().changeScene(SceneManager::SceneName::Gameplay);
			}
		}
	}

	void SceneGameOver::update(double time)
	{
	}

	void SceneGameOver::render()
	{
		// TODO once?
		//Game::instance().getAssetManager().DrawBackground(levels[currentLevelIndex]->levelId);

		renderSystem.update();
	}

	void SceneGameOver::loadScene()
	{
		//Game::instance().getAssetManager().DrawBackground(levels[currentLevelIndex]->levelId);

		SDL_Color white = { 255, 255, 255, 255 };
		game.getEntityFactory().createLabel("gameOverText", 350, 200, "GAME OVER", white);
		game.getEntityFactory().createLabel("restartText", 315, 250, "Press Space to restart", white);
	}

	void SceneGameOver::unloadScene()
	{
		game.getEntityFactory().destroyEntitiesWithComponent<TransformComponent>();
	}
}