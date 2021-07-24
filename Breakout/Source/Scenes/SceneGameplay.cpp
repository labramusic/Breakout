#include "SceneGameplay.hpp"

#include <Game.hpp>
#include <AssetManager.hpp>
#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/BrickComponent.hpp>
#include <ECS/Components/TextComponent.hpp>
#include <ECS/Systems/MovementSystem.hpp>
#include <ECS/Systems/CollisionSystem.hpp>
#include <ECS/Systems/RenderSystem.hpp>
#include <ECS/Entities/EntityFactory.hpp>
#include <Level.hpp>

namespace breakout
{
	SceneGameplay::SceneGameplay(MovementSystem &movementSystem, CollisionSystem &collisionSystem, RenderSystem &renderSystem) : 
		Scene(renderSystem), movementSystem(movementSystem), collisionSystem(collisionSystem)
	{
		levels.push_back(new Level("1"));
		levels.push_back(new Level("2"));
		levels.push_back(new Level("3"));
	}

	SceneGameplay::~SceneGameplay()
	{
		std::cout << "calling destructor of scene gameplay" << std::endl;

		for (auto it = levels.begin(); it != levels.end(); ++it) {
			delete *it;
		}
	}

	void SceneGameplay::handleEvent(const SDL_Event& event)
	{
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				// skip level
				nextLevel();
			}
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				SDL_Event sdlevent;
				sdlevent.type = SDL_QUIT;
				SDL_PushEvent(&sdlevent);
			}
		}
		//

		movementSystem.onEvent(event);
	}
	
	void SceneGameplay::update(double time)
	{
		movementSystem.update(time);
		collisionSystem.update(time);
	}

	void SceneGameplay::render()
	{
		// TODO once?
		Game::instance().getAssetManager().DrawBackground(levels[currentLevelIndex]->levelId);
		
		renderSystem.update();
	}

	void SceneGameplay::loadScene()
	{
		loadLevel();

		EntityFactory& entityFactory = Game::instance().getEntityFactory();
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
		Game::instance().getEntityFactory().destroyEntitiesWithComponent<TransformComponent>();
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

				Game::instance().getEntityFactory().createBrick(*brickType, xpos, ypos, level->blockWidth, level->blockHeight);
			}
		}
	}

	void SceneGameplay::unloadLevel()
	{
		// remove bricks
		Game::instance().getEntityFactory().destroyEntitiesWithComponent<BrickComponent>();
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

	void SceneGameplay::updateHUD(const std::string& tag, const std::string& text)
	{
		const Entity& elementHUD = *Game::instance().getEntityManager().getEntityByTag(tag);

		TextComponent& textC = Game::instance().getEntityManager().getComponent<TextComponent>(elementHUD);
		textC.text = text;

		TransformComponent& livesTr = Game::instance().getEntityManager().getComponent<TransformComponent>(elementHUD);
		SDL_Texture* tex = Game::instance().getAssetManager().CreateTextureFromText(textC.fontId, textC.text, textC.textColor);
		// get texture width and height
		SDL_QueryTexture(tex, nullptr, nullptr, &livesTr.width, &livesTr.height);
		// update text texture
		Game::instance().getAssetManager().addTexture(elementHUD.getTag(), *tex);
	}

	void SceneGameplay::gameOver()
	{
		currentLevelIndex = 0;
		unloadScene();
		loadScene();
	}
}
