#pragma once

#include <iostream>

namespace breakout
{
	class Vector2D
	{
	public:
		float x, y;

		Vector2D();
		Vector2D(float x, float y);

		Vector2D& Add(const Vector2D& vec);
		Vector2D& Subtract(const Vector2D& vec);
		Vector2D& Multiply(const Vector2D& vec); // elementwise
		Vector2D& Divide(const Vector2D& vec); // elementwise

		template <typename T>
		Vector2D& Scale(T const& scalar)
		{
			x *= scalar;
			y *= scalar;

			return *this;
		}

		Vector2D& Normalize();
		Vector2D& Zero();

		friend Vector2D operator+(Vector2D v1, const Vector2D& v2);
		friend Vector2D operator-(Vector2D v1, const Vector2D& v2);
		friend Vector2D operator*(Vector2D v1, const Vector2D& v2); // elementwise
		friend Vector2D operator/(Vector2D v1, const Vector2D& v2); // elementwise

		template <typename T>
		friend Vector2D operator*(Vector2D v, T const& scalar)
		{
			v *= scalar;
			return v;
		}
		template <typename T>
		friend Vector2D operator*(T const& scalar, Vector2D v)
		{
			v *= scalar;
			return v;
		}

		Vector2D& operator+=(const Vector2D& vec);
		Vector2D& operator-=(const Vector2D& vec);
		Vector2D& operator*=(const Vector2D& vec);
		Vector2D& operator/=(const Vector2D& vec);

		template <typename T>
		Vector2D& operator*=(T const& scalar)
		{
			return this->Scale(scalar);
		}

		friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
	};
}