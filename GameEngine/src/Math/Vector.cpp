#include "Math/Vector.h"

namespace Math
{
	Vector::Vector() noexcept
		: Vector(0.0f)
	{
	}
	Vector::Vector(float x) noexcept
		: x(x)
	{
	}

	Vector Vector::operator+(const Vector& other) noexcept
	{
		return Vector(x + other.x);
	}

	Vector Vector::operator-(const Vector& other) noexcept
	{
		return Vector(x - other.x);
	}

	Vector Vector::operator*(float scalar) noexcept
	{
		return Vector(x * scalar);
	}

	Vector Vector::operator/(float scalar) noexcept
	{
		if (scalar != 0.0f)
		{
			float invScalar = 1.0f / scalar;

			return Vector(x * invScalar);
		}

		return Vector();
	}

	float Vector::Length() noexcept
	{
		return x;
	}

	void Vector::Normalize() noexcept
	{
		float length = Length();
		if (length > 0.0f)
		{
			x /= length;
		}
	}

}