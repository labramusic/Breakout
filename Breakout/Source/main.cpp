#include "Game.hpp"
#include <SDL.h>
#include <iostream>

int main(int argc, const char* argv[])
{
	auto status = EXIT_FAILURE;

	try
	{
		breakout::Game game;
		//breakout::Game& game = breakout::Game::instance();
		bool success = game.init("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640);
		if (success)
		{
			status = game.run();
		}
		game.clean();
		//delete &game;
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

	return status;
}