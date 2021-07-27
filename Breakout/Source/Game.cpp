#include "Game.hpp"

#include "AssetManager.hpp"
#include "ECS/Entities/EntityManager.hpp"
#include "ECS/Entities/EntityFactory.hpp"
#include "Scenes/SceneManager.hpp"

#include <iostream>

namespace breakout
{
	Game::Game() : windowWidth(0), windowHeight(0), isRunning(false), event(), window(nullptr), renderer(nullptr),
	               assetManager(nullptr), entityManager(nullptr), entityFactory(nullptr), sceneManager(nullptr)
	{
	}

	Game::~Game()
	{
		std::cout << "calling destructor of game" << std::endl;
	}

	bool Game::Init(const char *title, int xpos, int ypos, int width, int height)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
			return false;
		}

		if (TTF_Init() != 0)
		{
			SDL_Log("Failed to initialize SDL_TTF: %s", SDL_GetError());
			return false;
		}

		const Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS;
		if (!(window = SDL_CreateWindow(title, xpos, ypos, width, height, flags)))
		{
			SDL_Log("Failed to create window! SDL: %s", SDL_GetError());
			return false;
		}

		// SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		if (!(renderer = SDL_CreateRenderer(window, -1, 0)))
		{
			SDL_Log("Failed to create renderer! SDL: %s", SDL_GetError());
			return false;
		}

		windowWidth = width;
		windowHeight = height;
		isRunning = true;

		assetManager = new AssetManager(*this);
		assetManager->AddFont("gameFont", "../Breakout/Assets/Fonts/SystemBold.fon", 32);
		assetManager->AddTexture("ball", "../Breakout/Assets/Textures/Ball.png");
		assetManager->AddTexture("paddle", "../Breakout/Assets/Textures/Paddle.png");
		assetManager->AddLevelFile("1", "../Breakout/Assets/Levels/Level_1.xml");
		assetManager->AddLevelFile("2", "../Breakout/Assets/Levels/Level_2.xml");
		assetManager->AddLevelFile("3", "../Breakout/Assets/Levels/Level_3.xml");
		
		entityManager = new EntityManager();
		entityFactory = new EntityFactory(*this);
		sceneManager = new SceneManager(*this);

		return true;
	}

	int Game::Run()
	{
		const int fps = 60;
		const double msPerUpdate = 1000. / fps;

		Uint32 previousFrameTime = SDL_GetTicks();
		double lag = 0.;

		while (isRunning)
		{
			const Uint32 currentFrameTime = SDL_GetTicks();
			const Uint32 elapsedTime = currentFrameTime - previousFrameTime;
			previousFrameTime = currentFrameTime;
			lag += elapsedTime;

			handleEvents();

			while (lag >= msPerUpdate)
			{
				// normalized value
				update(lag / msPerUpdate);
				lag -= msPerUpdate;
			}

			render();
		}

		return EXIT_SUCCESS;
	}

	void Game::handleEvents()
	{
		while (isRunning && SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			default:
				break;
			}

			// process system events
			sceneManager->HandleEvent(event);
		}
	}

	void Game::update(double time) const
	{		
		sceneManager->Update(time);

		entityManager->Refresh();
	}

	void Game::render() const
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		sceneManager->Render();

		// swap buffers
		SDL_RenderPresent(renderer);
	}

	void Game::Clean() const
	{
		std::cout << "Cleaning game" << std::endl;

		delete sceneManager;
		delete entityFactory;
		delete entityManager;
		delete assetManager;

		TTF_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}