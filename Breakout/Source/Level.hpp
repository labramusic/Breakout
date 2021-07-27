#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "BrickType.hpp"

namespace breakout
{
	class Level
	{
	public:
		Level(std::string levelId);
		~Level();

		std::string GetLevelId() const { return levelId; }
		int GetRowCount() const { return rowCount; }
		void SetRowCount(int rowCount) { this->rowCount = rowCount; }
		int GetColCount() const { return colCount; }
		void SetColCount(int colCount) { this->colCount = colCount; }
		int GetRowSpacing() const { return rowSpacing; }
		void SetRowSpacing(int rowSpacing) { this->rowSpacing = rowSpacing; }
		int GetColSpacing() const { return colSpacing; }
		void SetColSpacing(int colSpacing) { this->colSpacing = colSpacing; }
		float GetBlockWidth() const { return blockWidth; }
		void SetBlockWidth(const float w) { blockWidth = w; }
		float GetBlockHeight() const { return blockHeight; }
		void SetBlockHeight(const float h) { blockHeight = h; }
		const std::unordered_map<char, std::unique_ptr<BrickType>> &GetBrickTypes() const { return brickTypes; }
		void SetBrickTypes(std::unordered_map<char, std::unique_ptr<BrickType>> &brickTypes) { this->brickTypes = std::move(brickTypes); }
		std::string GetLayout() const { return layout; }
		void SetLayout(const std::string &layout) { this->layout = layout; }

	private:
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