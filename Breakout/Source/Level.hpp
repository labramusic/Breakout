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
		Level(std::string levelId) : levelId(std::move(levelId)), rowCount(0), colCount(0), rowSpacing(0), colSpacing(0)
		{
			blockWidth = 30.f;
			blockHeight = 30.f;
		}

		~Level();
		
		std::string levelId;
		int rowCount;
		int colCount;
		int rowSpacing;
		int colSpacing;
		float blockWidth;
		float blockHeight;
		std::unordered_map<std::string, std::unique_ptr<BrickType>> brickTypes;
		std::string* layout = nullptr;
	};

}