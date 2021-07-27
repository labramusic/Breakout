#pragma once

#include "Component.hpp"
#include <BrickType.hpp>

namespace breakout
{
	class BrickComponent : public Component
	{
	public:
		BrickComponent(const BrickType &type) : brickType(type), hitPoints(type.GetHitPoints()) {}

		const BrickType &GetBrickType() const { return brickType; }
		int GetHitPoints() const { return hitPoints; }
		void SetHitPoints(int hitPoints) { this->hitPoints = hitPoints; }

		void TakeHit() { --hitPoints; }
		
	private:
		const BrickType &brickType;
		int hitPoints;
	};
}
