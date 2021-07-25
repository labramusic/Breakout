#pragma once

#include "Component.hpp"
#include "Vector2D.hpp"

namespace breakout
{
	class MoveComponent : public Component
	{
	public:
		MoveComponent() : velocity(Vector2D(0.f, 0.f)), movementSpeed(1) {}
		MoveComponent(const Vector2D v, const int speed) : velocity(v), movementSpeed(speed) {}
		MoveComponent(const int speed) : velocity(Vector2D(0.f, 0.f)), movementSpeed(speed) {}
		
		Vector2D velocity;
		int movementSpeed;
	};
}
