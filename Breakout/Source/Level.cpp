#include "Level.hpp"

namespace breakout
{
	Level::~Level()
	{
		for (auto it = brickTypes.begin(); it != brickTypes.end(); ++it) {
			it->second.reset();
		}
		
		delete[] layout;
		layout = nullptr;
	}
}