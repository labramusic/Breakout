#pragma once

#include "Component.hpp"
#include <BrickType.hpp>

namespace breakout
{
	class BrickComponent : public Component
	{
	public:
		BrickComponent(const BrickType& type) : brickType(type), hitPoints(type.hitPoints) {}

		const BrickType &brickType;
		int hitPoints;
	};
}
