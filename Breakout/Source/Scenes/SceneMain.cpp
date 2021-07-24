#include "SceneMain.hpp"

#include "Game.hpp"
#include "SceneManager.hpp"
#include "ECS/Components/TransformComponent.hpp"

namespace breakout
{
	SceneMain::SceneMain(RenderSystem &renderSystem) : Scene(renderSystem)
	{
	}

	SceneMain::~SceneMain()
	{
	}

	void SceneMain::handleEvent(const SDL_Event& event)
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

		std::cout << "load main scene" << std::endl;

		SDL_Color white = { 255, 255, 255, 255 };
		Game::instance().getEntityFactory().createLabel("gameTitle", 50, 50, "BREAKOUT", white);
		Game::instance().getEntityFactory().createLabel("playMsg", 50, 200, "Press Space to play", white);
	}

	void SceneMain::unloadScene()
	{
		Game::instance().getEntityFactory().destroyEntitiesWithComponent<TransformComponent>();
	}
}