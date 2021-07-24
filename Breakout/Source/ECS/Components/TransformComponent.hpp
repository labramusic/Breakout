#pragma once

#include "Component.hpp"
#include <Vector2D.hpp>

namespace breakout
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent(const float x, const float y, const int w, const int h, const int sc)
		{
			position = Vector2D(x, y);
			initialPos = position;
			width = w;
			height = h;
			scale = sc;
		}

		TransformComponent(const float x, const float y, const int w, const int h)
		: TransformComponent(x, y, w, h, 1)
		{
		}

		TransformComponent(const float x, const float y) : TransformComponent(x, y, 0, 0, 1)
		{}

		TransformComponent() : TransformComponent(0, 0, 0, 0, 1)
		{
		}
		
		Vector2D position;
		Vector2D initialPos;
		// rotation

		int width = 30;
		int height = 30;
		int scale = 1;	
	};
}
