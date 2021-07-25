#pragma once

#include "System.hpp"

namespace breakout
{
	class RenderSystem : public System
	{
	public:
		RenderSystem(const Game &game);
		//RenderSystem() : System() {}
		virtual ~RenderSystem();
		
		void update();
	};
}