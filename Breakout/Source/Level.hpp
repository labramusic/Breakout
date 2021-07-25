#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "BrickType.hpp"

namespace breakout
{
	class Level
	{
	public:
		Level(std::string levelId);
		~Level();
		
		std::string levelId;
		int rowCount;
		int colCount;
		int rowSpacing;
		int colSpacing;
		float blockWidth;
		float blockHeight;

		std::unordered_map<char, std::unique_ptr<BrickType>> brickTypes;
		std::string layout;
	};
}