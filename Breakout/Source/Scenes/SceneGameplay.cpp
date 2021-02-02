#include "SceneGameplay.hpp"

#include "Game.hpp"
#include "ECS/Components/BrickComponent.hpp"
#include "ECS/Components/TextComponent.hpp"

namespace breakout
{
	SceneGameplay::SceneGameplay()
	{
		entityFactory = EntityFactory(Game::instance().getEntityManager());
		renderSystem = RenderSystem(Game::instance().getEntityManager());
		movementSystem = MovementSystem(Game::instance().getEntityManager(), *this);
		collisionSystem = CollisionSystem(Game::instance().getEntityManager(), *this);

		levels.push_back(new Level("1"));
		levels.push_back(new Level("2"));
		levels.push_back(new Level("3"));
	}

	void SceneGameplay::handleEvent(const SDL_Event& event)
	{
		movementSystem.onEvent(event);
	}
	
	void SceneGameplay::update(double time)
	{
		movementSystem.update(time);
		collisionSystem.update(time);
	}

	void SceneGameplay::render()
	{
		Game::instance().getAssetManager().DrawBackground(levels[currentLevelIndex]->levelId);
		
		renderSystem.update();
	}

	void SceneGameplay::loadScene()
	{
		loadLevel();

		entityFactory.createPaddle();
		entityFactory.createBall();

		// create UI
		SDL_Color white = { 255, 255, 255, 255 };
		entityFactory.createLabel("levelHUD", 10, 0, "Level 1", white);
		entityFactory.createLabel("scoreHUD", 350, 0, "Score: 0", white);
		entityFactory.createLabel("livesHUD", 720, 0, "Lives: 3", white);

		score = 0;
		lives = 3;
	}

	void SceneGameplay::unloadScene()
	{
		auto& entityManager = Game::instance().getEntityManager();
		for (auto const& entity : entityManager.getEntitiesWithComponent<TransformComponent>())
		{
			entityManager.removeEntity(*entity);
		}
		entityManager.refresh();
	}


	void SceneGameplay::loadLevel()
	{
		Game::instance().getAssetManager().parseLevel(*levels[currentLevelIndex]);

		// create level
		auto& level = levels[currentLevelIndex];
		const float xoffset = 5.f;
		const float yoffset = 25.f;

		const int windowWidth = Game::instance().getWindowWidth();
		level->blockWidth = (windowWidth - 2 * xoffset - (level->colCount - 1) * level->colSpacing) / level->colCount;
		level->blockHeight = level->blockWidth / 1.25f;

		for (auto i = 0; i < level->rowCount; ++i)
		{
			for (auto j = 0; j < level->colCount; ++j)
			{
				const float xpos = xoffset + j * (level->blockWidth + level->colSpacing);
				const float ypos = yoffset + i * (level->blockHeight + level->rowSpacing);

				auto brickId = level->layout[i * level->colCount + j];
				if (level->brickTypes.find(brickId) == level->brickTypes.end())
					continue;
				auto& brickType = level->brickTypes[brickId];

				entityFactory.createBrick(*brickType, xpos, ypos, level->blockWidth, level->blockHeight);
			}
		}
	}

	void SceneGameplay::unloadLevel()
	{
		// remove bricks
		auto& entityManager = Game::instance().getEntityManager();
		for (auto const& entity : entityManager.getEntitiesWithComponent<BrickComponent>())
		{
			entityManager.removeEntity(*entity);
		}
		entityManager.refresh();
	}

	void SceneGameplay::nextLevel()
	{
		++currentLevelIndex;
		if (currentLevelIndex < levels.size())
		{
			movementSystem.resetPositions();
			unloadLevel();
			loadLevel();
			updateHUD("levelHUD", "Level " + std::to_string(currentLevelIndex + 1));
		}
		else
		{
			gameOver();
		}
	}

	void SceneGameplay::gameOver()
	{
		currentLevelIndex = 0;
		unloadScene();
		loadScene();
	}

	void SceneGameplay::updateHUD(const std::string& tag, const std::string& text)
	{
		const auto& elementHUD = Game::instance().getEntityManager().getEntityByTag(tag);
		auto& textC = Game::instance().getEntityManager().getComponent<TextComponent>(*elementHUD);
		textC.text = text;
		SDL_Texture* tex = Game::instance().getAssetManager().CreateTextureFromText(textC.fontId, textC.text, textC.textColor);
		auto& livesTr = Game::instance().getEntityManager().getComponent<TransformComponent>(*elementHUD);
		// get texture width and height
		SDL_QueryTexture(tex, nullptr, nullptr, &livesTr.width, &livesTr.height);
		Game::instance().getAssetManager().addTexture(elementHUD->getTag(), *tex);
	}
}
