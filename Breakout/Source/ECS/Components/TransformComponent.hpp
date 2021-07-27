#pragma once

#include "Component.hpp"
#include <Vector2D.hpp>

namespace breakout
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent(const float x, const float y, const int w, const int h, const int sc) :
			position(Vector2D(x, y)), initialPos(position), width(w), height(h), scale(sc) {}
		
		TransformComponent(const float x, const float y, const int w, const int h) : TransformComponent(x, y, w, h, 1) {}
		TransformComponent(const float x, const float y) : TransformComponent(x, y, 0, 0, 1) {}
		TransformComponent() : TransformComponent(0, 0, 0, 0, 1) {}

		Vector2D GetPosition() const { return position; }
		void SetPosition(const Vector2D &position) { this->position = position; }
		void SetPositionX(float x) { position.x = x; }
		void SetPositionY(float y) { position.y = y; }
		Vector2D GetInitialPos() const { return initialPos; }
		int GetWidth() const { return width; }
		void SetWidth(const int w) { width = w; }
		int GetHeight() const { return height; }
		void SetHeight(const int h) { height = h; }
		int GetScale() const { return scale; }
		
	private:
		Vector2D position;
		Vector2D initialPos;
		int width;
		int height;
		int scale;	
	};
}
