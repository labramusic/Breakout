#include <iostream>

#include "Game.hpp"
#include <SDL.h>

int main(int argc, const char* argv[])
{
	auto success = EXIT_FAILURE;

	try
	{
		SDL_SetMainReady();
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::string const message = "Failed to initialize SDL2! Error: " + std::string(SDL_GetError());
			throw std::runtime_error(message);
		}

		if (TTF_Init() != 0)
		{
			std::string const message = "Failed to initialize SDL_TTF! Error: " + std::string(SDL_GetError());
			throw std::runtime_error(message);
		}

		auto& game = breakout::Game::instance();
		const Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS;
		game.init("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, flags);		
		success = game.run();
		game.clean();
	}
	catch(const std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		std::cin.get();
	}
	catch (...)
	{
		std::cout << "Unknown exception!" << std::endl;
		std::cin.get();
	}

	return success;
}