#include "System.hpp"
#include <Game.hpp>

namespace breakout
{
	System::System(Game &game) : game(game), entityManager(game.GetEntityManager()) {}
	System::~System() {}
}