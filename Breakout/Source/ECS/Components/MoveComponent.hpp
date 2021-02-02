#pragma once

#include "Component.hpp"
#include "Vector2D.hpp"

namespace breakout
{
	class MoveComponent : public Component
	{
	public:
		MoveComponent()
		{
			velocity.Zero();
			movementSpeed = 1;
		}

		MoveComponent(const Vector2D v, const int speed)
		{
			velocity = v;
			movementSpeed = speed;
		}

		MoveComponent(const int speed)
		{
			velocity.Zero();
			movementSpeed = speed;
		}
		
		Vector2D velocity;
		int movementSpeed;
	};
}
