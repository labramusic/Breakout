#include "SceneGameOver.hpp"

#include <Game.hpp>
#include <ECS/Entities/EntityFactory.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Systems/RenderSystem.hpp>

#include "SceneManager.hpp"
#include <AssetManager.hpp>

namespace breakout
{
	SceneGameOver::SceneGameOver(Game &game, RenderSystem &renderSystem) : Scene(game, renderSystem)
	{
	}

	SceneGameOver::~SceneGameOver()
	{
	}

	void SceneGameOver::HandleEvent(const SDL_Event &event)
	{
		Scene::HandleEvent(event);

		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				// restart game
				game.GetSceneManager().ChangeScene(SceneManager::SceneName::Gameplay);
			}
		}
	}

	void SceneGameOver::Update(double time)
	{
	}

	void SceneGameOver::Render()
	{
		game.GetAssetManager().DrawBackground(std::string("1"));

		renderSystem.Update();
	}

	void SceneGameOver::LoadScene()
	{
		const SDL_Color white = { 255, 255, 255, 255 };
		game.GetEntityFactory().CreateLabel("gameOverText", 350.f, 200.f, "GAME OVER", white);
		game.GetEntityFactory().CreateLabel("restartText", 315.f, 250.f, "Press Space to restart", white);
	}

	void SceneGameOver::UnloadScene()
	{
		game.GetEntityFactory().destroyEntitiesWithComponent<TransformComponent>();
	}
}