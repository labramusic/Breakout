#include "Game.hpp"
#include <iostream>
#include <string>
#include "Scenes/SceneManager.hpp"

namespace breakout
{
	Game::Game() : windowWidth(0), windowHeight(0), isRunning(false), event(), window(nullptr), renderer(nullptr),
	               assetManager(nullptr), entityManager(nullptr), sceneManager(nullptr)
	{
	}

	Game::~Game()
	{
		std::cout << "calling destructor of game" << std::endl;

		//delete sceneManager;
		//delete entityManager;
		//delete assetManager;
	}

	bool Game::init(const char* title, int xpos, int ypos, int width, int height)
	{
		//srand(time(NULL));

		// to avoid some errors ?
		//SDL_SetMainReady();
		//SDL_INIT_VIDEO | SDL_INIT_AUDIO
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			//std::string const message = "Failed to initialize SDL: " + std::string(SDL_GetError());
			//throw std::runtime_error(message);
			SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
			return false;
		}

		if (TTF_Init() != 0)
		{
			//std::string const message = "Failed to initialize SDL_TTF! Error: " + std::string(SDL_GetError());
			//throw std::runtime_error(message);
			SDL_Log("Failed to initialize SDL_TTF: %s", SDL_GetError());
			return false;
		}

		/*if (IMG_Init(IMG_INIT_PNG) == 0)
		{
			SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
			return false;
		}*/

		const Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS;
		if (!(window = SDL_CreateWindow(title, xpos, ypos, width, height, flags)))
		{
			//std::string message = "Failed to create window! SDL: ";
			//message += SDL_GetError();
			//std::cout << message << std::endl;
			SDL_Log("Failed to create window! SDL: %s", SDL_GetError());
			return false;
		}

		// TODO choppy, discrete with vsync
		// SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		if (!(renderer = SDL_CreateRenderer(window, -1, 0)))
		{
			//std::string message = "Failed to create renderer! SDL: ";
			//message += SDL_GetError();
			//std::cout << message << std::endl;
			SDL_Log("Failed to create renderer! SDL: %s", SDL_GetError());
			return false;
		}

		windowWidth = width;
		windowHeight = height;
		isRunning = true;

		assetManager = new AssetManager();
		assetManager->addFont("gameFont", "../Breakout/Assets/Fonts/SystemBold.fon", 32);
		assetManager->addTexture("ball", "../Breakout/Assets/Textures/Ball.png");
		assetManager->addTexture("paddle", "../Breakout/Assets/Textures/Paddle.png");
		assetManager->addLevelFile("1", "../Breakout/Assets/Levels/Level_1.xml");
		assetManager->addLevelFile("2", "../Breakout/Assets/Levels/Level_2.xml");
		assetManager->addLevelFile("3", "../Breakout/Assets/Levels/Level_3.xml");
		
		entityManager = new EntityManager();
		entityFactory = new EntityFactory(*entityManager);
		sceneManager = new SceneManager();

		//	mTicksCount = SDL_GetTicks();
		return true;
	}

	int Game::run()
	{
		//ensure at least 16ms elapses between frames
		//while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

		//converted to seconds
		//float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
		//if (deltaTime > 0.05f)
		//{
		//	deltaTime = 0.05f;
		//}
		//mTicksCount = SDL_GetTicks();
		//

		const int fps = 60;
		const int msPerUpdate = 1000 / fps;

		auto previousFrameTime = SDL_GetTicks();
		auto lag = 0u;

		while (isRunning)
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

		return EXIT_SUCCESS;
	}

	void Game::handleEvents()
	{
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			default:
				break;
			}

			//const Uint8* keyState = SDL_GetKeyboardState(NULL);

			// process system events
			sceneManager->handleEvent(event);

			// TODO
			//const Uint8* state = SDL_GetKeyboardState(NULL);
			//if (state[SDL_SCANCODE_W])
		}
	}

	// float deltaTime?
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
		std::cout << "Cleaning game" << std::endl;

		// TODO
		delete sceneManager;
		delete entityFactory;
		delete entityManager;
		delete assetManager;
		//

		TTF_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}
