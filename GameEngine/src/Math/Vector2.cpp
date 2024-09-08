#include <cmath>

#include "Math/Vector2.h"

namespace Math
{
	Vector2::Vector2() noexcept
		: glm::vec2(0.0f)
	{
	}

	Vector2::Vector2(float scalar) noexcept
		: glm::vec2(scalar, scalar)
	{
	}

	Vector2::Vector2(float x, float y) noexcept
		: glm::vec2(x, y)
	{
	}

	/*
	Vector2 Vector2::operator+(const Vector2& other) noexcept
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 Vector2::operator-(const Vector2& other) noexcept
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 Vector2::operator*(float scalar) noexcept
	{
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 Vector2::operator/(float scalar) noexcept
	{
		if (scalar != 0.0f)
		{
			float invScalar = 1.0f / scalar;

			return Vector2(x * invScalar, y * invScalar);
		}

		return Vector2();
	}

	float Vector2::Length() noexcept
	{
		return sqrt(x * x + y * y);
	}

	void Vector2::Normalize() noexcept
	{
		float length = Length();
		if (length > 0.0f)
		{
			x /= length;
			y /= length;
		}
	}*/

}