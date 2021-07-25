#include "System.hpp"
#include <Game.hpp>

namespace breakout
{
	System::System(const Game &game) : game(game), entityManager(game.getEntityManager()) {}
	System::~System() {}
}