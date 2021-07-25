#pragma once

#include "System.hpp"

namespace breakout
{
	class RenderSystem : public System
	{
	public:
		explicit RenderSystem(const Game &game);
		virtual ~RenderSystem();
		
		void update();
	};
}