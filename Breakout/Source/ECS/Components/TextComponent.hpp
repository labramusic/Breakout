#pragma once

#include "Component.hpp"
#include <string>
#include <utility>

namespace  breakout
{
	class TextComponent : public Component
	{
	public:
		TextComponent(std::string text, std::string fontId, SDL_Color color) :
			text(std::move(text)), fontId(std::move(fontId)), textColor(color)
		{
		}

		std::string GetText() const { return text; }
		void SetText(const std::string &text) { this->text = text; }
		std::string GetFontId() const { return fontId; }
		SDL_Color GetTextColor() const { return textColor; }
		
	private:
		std::string text;
		std::string fontId;
		SDL_Color textColor;
	};
}
