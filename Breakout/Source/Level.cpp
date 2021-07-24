#include "Level.hpp"
#include <iostream>

namespace breakout
{
	Level::~Level()
	{
		for (auto it = brickTypes.begin(); it != brickTypes.end(); ++it) {
			it->second.reset();
		}
		
		delete[] layout;
		layout = nullptr;
		std::cout << "calling destructor of level" << std::endl;
	}
}