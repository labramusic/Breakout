#include "Vector2D.hpp"

namespace breakout
{

	Vector2D::Vector2D()
	{
		x = y = 0.0f;
	}

	Vector2D::Vector2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2D& Vector2D::Add(const Vector2D& vec)
	{
		x += vec.x;
		y += vec.y;

		return *this;
	}

	Vector2D& Vector2D::Subtract(const Vector2D& vec)
	{
		x -= vec.x;
		y -= vec.y;

		return *this;
	}

	Vector2D& Vector2D::Multiply(const Vector2D& vec)
	{
		x *= vec.x;
		y *= vec.y;

		return *this;
	}

	Vector2D& Vector2D::Divide(const Vector2D& vec)
	{
		x /= vec.x;
		y /= vec.y;

		return *this;
	}


	Vector2D& Vector2D::Normalize()
	{
		if (abs(x) <= 10E-6f && abs(y) <= 10E-6f) return *this;

		const float magnitude = sqrt(pow(x, 2) + pow(y, 2));
		*this *= 1.0f / magnitude;

		return *this;
	}


	Vector2D& Vector2D::Zero()
	{
		this->x = 0;
		this->y = 0;

		return *this;
	}

	Vector2D operator+(Vector2D v1, const Vector2D& v2)
	{
		v1 += v2;
		return v1;
	}

	Vector2D operator-(Vector2D v1, const Vector2D& v2)
	{
		v1 -= v2;
		return v1;
	}

	Vector2D operator*(Vector2D v1, const Vector2D& v2)
	{
		v1 *= v2;
		return v1;
	}

	Vector2D operator/(Vector2D v1, const Vector2D& v2)
	{
		v1 /= v2;
		return v1;
	}

	Vector2D& Vector2D::operator+=(const Vector2D& vec)
	{
		return this->Add(vec);
	}

	Vector2D& Vector2D::operator-=(const Vector2D& vec)
	{
		return this->Subtract(vec);
	}

	Vector2D& Vector2D::operator*=(const Vector2D& vec)
	{
		return this->Multiply(vec);
	}

	Vector2D& Vector2D::operator/=(const Vector2D& vec)
	{
		return this->Divide(vec);
	}

	std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
	{
		return stream << "(" << vec.x << "," << vec.y << ")";
	}
}