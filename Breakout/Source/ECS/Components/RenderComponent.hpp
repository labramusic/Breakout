#pragma once

#include "Component.hpp"

namespace breakout
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent(std::string tId) : tId(std::move(tId)) {}

		std::string GetTId() const { return tId; }
		
	private:
		std::string tId;
	};
}