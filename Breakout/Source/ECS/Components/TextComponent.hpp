#pragma once

#include <string>
#include <utility>
#include "Component.hpp"

namespace  breakout
{
	class TextComponent : public Component
	{
	public:
		TextComponent(std::string text, std::string fontId, SDL_Color color) :
			text(std::move(text)), fontId(std::move(fontId)), textColor(color)
		{
		}

		std::string text;
		std::string fontId;
		SDL_Color textColor;
	};
}
