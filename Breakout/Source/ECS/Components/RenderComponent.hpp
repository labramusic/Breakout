#pragma once

#include "Component.hpp"

namespace breakout
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent(const std::string tId) : tId(tId) {}

		std::string tId;
	};

}