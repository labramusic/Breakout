#include "SceneGameplay.hpp"

#include <Game.hpp>
#include <AssetManager.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/BrickComponent.hpp>
#include <ECS/Components/TextComponent.hpp>
#include <ECS/Systems/MovementSystem.hpp>
#include <ECS/Systems/CollisionSystem.hpp>
#include <ECS/Systems/RenderSystem.hpp>
#include <ECS/Entities/EntityManager.hpp>
#include <ECS/Entities/EntityFactory.hpp>
#include <Level.hpp>

#include "SceneManager.hpp"

namespace breakout
{
	SceneGameplay::SceneGameplay(Game &game, MovementSystem &movementSystem, CollisionSystem &collisionSystem, RenderSystem &renderSystem) :
		Scene(game, renderSystem), entityManager(game.GetEntityManager()), movementSystem(movementSystem), collisionSystem(collisionSystem), isGameOver(false)
	{
		levels.push_back(std::make_unique<Level>("1"));
		levels.push_back(std::make_unique<Level>("2"));
		levels.push_back(std::make_unique<Level>("3"));

		for (int i = 0; i < levels.size(); ++i)
		{
			game.GetAssetManager().ParseLevel(*levels[i]);
		}
	}

	SceneGameplay::~SceneGameplay()
	{
		std::cout << "calling destructor of scene gameplay" << std::endl;
	}

	void SceneGameplay::HandleEvent(const SDL_Event &event)
	{
		Scene::HandleEvent(event);

		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				nextLevel();
			}
		}

		movementSystem.OnEvent(event);
	}
	
	void SceneGameplay::Update(double time)
	{
		movementSystem.Update(time);
		collisionSystem.Update(time);

		if (!isGameOver && levelFinished())
			nextLevel();
	}

	void SceneGameplay::Render()
	{
		game.GetAssetManager().DrawBackground(levels[currentLevelIndex]->GetLevelId());
		
		renderSystem.Update();
	}

	void SceneGameplay::LoadScene()
	{
		loadLevel();

		EntityFactory &entityFactory = game.GetEntityFactory();
		entityFactory.CreatePaddle();
		entityFactory.CreateBall();

		// create UI
		const SDL_Color white = { 255, 255, 255, 255 };
		entityFactory.CreateLabel("levelHUD", 10.f, 0.f, "Level 1", white);
		entityFactory.CreateLabel("scoreHUD", 350.f, 0.f, "Score: 0", white);
		entityFactory.CreateLabel("livesHUD", 720.f, 0.f, "Lives: 3", white);

		score = 0;
		lives = 3;
		isGameOver = false;
	}

	void SceneGameplay::UnloadScene()
	{
		game.GetEntityFactory().destroyEntitiesWithComponent<TransformComponent>();
	}

	void SceneGameplay::loadLevel()
	{
		// create level
		std::unique_ptr<Level> &level = levels[currentLevelIndex];
		const float xoffset = 5.f;
		const float yoffset = 25.f;

		const int windowWidth = game.GetWindowWidth();
		level->SetBlockWidth((windowWidth - 2 * xoffset - (level->GetColCount() - 1) * level->GetColSpacing()) / level->GetColCount());
		level->SetBlockHeight(level->GetBlockWidth() / 1.25f);

		for (int i = 0; i < level->GetRowCount(); ++i)
		{
			for (int j = 0; j < level->GetColCount(); ++j)
			{
				const float xpos = xoffset + j * (level->GetBlockWidth() + level->GetColSpacing());
				const float ypos = yoffset + i * (level->GetBlockHeight() + level->GetRowSpacing());

				char brickId = level->GetLayout()[i * level->GetColCount() + j];
				if (level->GetBrickTypes().find(brickId) == level->GetBrickTypes().end())
					continue;

				game.GetEntityFactory().CreateBrick(*level->GetBrickTypes().at(brickId), xpos, ypos, level->GetBlockWidth(), level->GetBlockHeight());
			}
		}
	}

	void SceneGameplay::unloadLevel() const
	{
		// remove bricks
		game.GetEntityFactory().destroyEntitiesWithComponent<BrickComponent>();
	}

	void SceneGameplay::nextLevel()
	{
		++currentLevelIndex;
		if (currentLevelIndex < levels.size())
		{
			movementSystem.ResetPositions();
			unloadLevel();
			loadLevel();
			updateHUD("levelHUD", "Level " + std::to_string(currentLevelIndex + 1));
		}
		else
		{
			gameOver();
		}
	}

	void SceneGameplay::updateHUD(const std::string& tag, const std::string& text) const
	{
		const Entity &elementHUD = *game.GetEntityManager().GetEntityByTag(tag);

		TextComponent &textC = game.GetEntityManager().GetComponent<TextComponent>(elementHUD);
		textC.SetText(text);

		TransformComponent &livesTr = game.GetEntityManager().GetComponent<TransformComponent>(elementHUD);
		SDL_Texture *tex = game.GetAssetManager().CreateTextureFromText(textC.GetFontId(), textC.GetText(), textC.GetTextColor());
		// get texture width and height
		int w, h;
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		livesTr.SetWidth(w);
		livesTr.SetHeight(h);
		game.GetAssetManager().AddTexture(tag, *tex);
	}

	void SceneGameplay::LoseLife()
	{
		--lives;
		if (lives == 0)
		{
			gameOver();
		}
		else
		{
			updateHUD("livesHUD", "Lives: " + std::to_string(lives));
		}
	}

	void SceneGameplay::gameOver()
	{
		isGameOver = true;
		currentLevelIndex = 0;
		game.GetSceneManager().ChangeScene(SceneManager::SceneName::GameOver);
	}

	bool SceneGameplay::levelFinished() const
	{
		// if there are bricks other than impenetrable remaining
		std::vector<Entity*> bricks = entityManager.GetEntitiesWithComponent<BrickComponent>();
		for (Entity *const &brick : bricks)
		{
			if (entityManager.GetComponent<BrickComponent>(*brick).GetBrickType().GetHitPoints() != -1)
			{
				return false;
			}
		}

		return true;
	}

	void SceneGameplay::AddScore(int points)
	{
		score += points;
		updateHUD("scoreHUD", "Score: " + std::to_string(score));
	}
}