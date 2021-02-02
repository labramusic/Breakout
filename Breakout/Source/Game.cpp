#include "Game.hpp"
#include <iostream>
#include <string>

namespace breakout
{
	Game::Game() : windowWidth(0), windowHeight(0), running(false), event(), window(nullptr), renderer(nullptr),
	               assetManager(nullptr), entityManager(nullptr), sceneManager(nullptr)
	{
	}


	Game::~Game()
	{
		delete assetManager;
		delete entityManager;
		delete sceneManager;
	}

	void Game::init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags)
	{
		if (!(window = SDL_CreateWindow(title, xpos, ypos, width, height, flags)))
		{
			std::string message = "Window failed to be created! SDL: ";
			message += SDL_GetError();
			std::cout << message << std::endl;
		}

		if (!(renderer = SDL_CreateRenderer(window, -1, 0)))
		{
			std::string message = "Renderer failed to be created! SDL: ";
			message += SDL_GetError();
			std::cout << message << std::endl;
		}
		windowWidth = width;
		windowHeight = height;
		running = true;

		assetManager = new AssetManager();
		assetManager->addFont("gameFont", "../Breakout/Assets/Fonts/SystemBold.fon", 32);
		assetManager->addTexture("ball", "../Breakout/Assets/Textures/Ball.png");
		assetManager->addTexture("paddle", "../Breakout/Assets/Textures/Paddle.png");
		assetManager->addLevelFile("1", "../Breakout/Assets/Levels/Level_1.xml");
		assetManager->addLevelFile("2", "../Breakout/Assets/Levels/Level_2.xml");
		assetManager->addLevelFile("3", "../Breakout/Assets/Levels/Level_3.xml");
		
		entityManager = new EntityManager();
		sceneManager = new SceneManager();
	}

	int Game::run()
	{
		const int fps = 60;
		const int msPerUpdate = 1000 / fps;

		auto previousFrameTime = SDL_GetTicks();
		auto lag = 0u;

		while (running)
		{
			const auto currentFrameTime = SDL_GetTicks();
			const auto elapsedTime = currentFrameTime - previousFrameTime;
			previousFrameTime = currentFrameTime;
			lag += elapsedTime;

			handleEvents();

			while (lag >= msPerUpdate)
			{
				// interpolated velocity value
				update(1.0 - static_cast<double>(lag - msPerUpdate) / msPerUpdate);

				lag -= msPerUpdate;
			}

			render();
		}

		clean();
		return EXIT_SUCCESS;
	}

	void Game::handleEvents()
	{
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;

			default:
				break;
			}

			// process system events
			sceneManager->handleEvent(event);
		}
	}

	void Game::update(double time)
	{
		entityManager->refresh();
		
		sceneManager->update(time);
	}

	void Game::render()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		sceneManager->render();

		// swap buffers
		SDL_RenderPresent(renderer);
	}

	void Game::clean()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

}
