#include "Level.hpp"
#include <iostream>

namespace breakout
{
	Level::Level(std::string levelId) : levelId(std::move(levelId)), rowCount(0), colCount(0), rowSpacing(0), colSpacing(0), blockWidth(30.f), blockHeight(30.f)
	{
		layout.reserve(rowCount * colCount);
	}

	Level::~Level()
	{
		std::cout << "calling destructor of level" << std::endl;
	}
}