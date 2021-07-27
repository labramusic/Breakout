#include "SceneMain.hpp"

#include <Game.hpp>
#include <ECS/Entities/EntityFactory.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Systems/RenderSystem.hpp>

#include "SceneManager.hpp"

namespace breakout
{
	SceneMain::SceneMain(Game &game, RenderSystem &renderSystem) : Scene(game, renderSystem)
	{
	}

	SceneMain::~SceneMain()
	{
	}

	void SceneMain::HandleEvent(const SDL_Event &event)
	{
		Scene::HandleEvent(event);
		
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				// start game
				game.GetSceneManager().ChangeScene(SceneManager::SceneName::Gameplay);
			}
		}
	}

	void SceneMain::Update(double time)
	{
	}

	void SceneMain::Render()
	{
		renderSystem.Update();
	}

	void SceneMain::LoadScene()
	{
		const SDL_Color white = { 255, 255, 255, 255 };
		game.GetEntityFactory().CreateLabel("gameTitle", 350.f, 200.f, "BREAKOUT", white);
		game.GetEntityFactory().CreateLabel("playMsg", 320.f, 250.f, "Press Space to play", white);
	}

	void SceneMain::UnloadScene()
	{
		game.GetEntityFactory().destroyEntitiesWithComponent<TransformComponent>();
	}
}