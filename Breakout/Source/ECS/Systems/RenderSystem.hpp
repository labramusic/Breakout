#pragma once

#include "System.hpp"

namespace breakout
{
	class RenderSystem : public System
	{
	public:
		RenderSystem(EntityManager& entityManager) : System(entityManager) {}
		RenderSystem() : System() {}
		
		void update();
	};
}