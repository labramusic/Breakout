#include "Scene.hpp"
#include "SceneManager.hpp"
#include <Game.hpp>

#include <iostream>

namespace breakout
{
	Scene::Scene(const Game &game, RenderSystem& renderSystem) : game(game), renderSystem(renderSystem)
	{
	}

	Scene::~Scene() 
	{
	}

	void Scene::handleEvent(const SDL_Event& event)
	{
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				SDL_Event sdlevent;
				sdlevent.type = SDL_QUIT;
				SDL_PushEvent(&sdlevent);
			}
		}
	}
}