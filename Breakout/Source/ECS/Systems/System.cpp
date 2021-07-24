#include "System.hpp"

namespace breakout
{
	System::System(EntityManager& entityManager) : entityManager(entityManager) {}
	System::~System() {}
}