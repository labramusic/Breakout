#pragma once
#include <SDL_events.h>

namespace breakout
{
	class Scene
	{
	public:
		virtual ~Scene() = default;
		
		virtual void update(double time) = 0;
		virtual void render() = 0;
		virtual void handleEvent(const SDL_Event& event) = 0;
		
		virtual void loadScene() = 0;
		virtual void unloadScene() = 0;
	};
}
