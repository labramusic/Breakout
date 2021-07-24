#pragma once

#include "System.hpp"

namespace breakout
{
	class RenderSystem : public System
	{
	public:
		RenderSystem(EntityManager& entityManager);
		//RenderSystem() : System() {}
		virtual ~RenderSystem();
		
		void update();
	};
}