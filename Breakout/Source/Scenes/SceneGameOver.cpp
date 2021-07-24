#include "SceneGameOver.hpp"

#include <Game.hpp>
#include <ECS/Entities/EntityFactory.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Systems/RenderSystem.hpp>

#include "SceneManager.hpp"

namespace breakout
{
	SceneGameOver::SceneGameOver(RenderSystem& renderSystem) : Scene(renderSystem)
	{
	}

	SceneGameOver::~SceneGameOver()
	{
	}

	void SceneGameOver::handleEvent(const SDL_Event& event)
	{
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				// start game
				Game::instance().getSceneManager().changeScene(SceneManager::SceneName::Gameplay);
			}
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				SDL_Event sdlevent;
				sdlevent.type = SDL_QUIT;
				SDL_PushEvent(&sdlevent);
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
		Game::instance().getEntityFactory().createLabel("gameOverText", 350, 200, "GAME OVER", white);
		Game::instance().getEntityFactory().createLabel("restartText", 315, 250, "Press Space to restart", white);
	}

	void SceneGameOver::unloadScene()
	{
		Game::instance().getEntityFactory().destroyEntitiesWithComponent<TransformComponent>();
	}
}