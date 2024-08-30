#include <cmath>

#include "Math/Vector4.h"

namespace Math
{
	Vector4::Vector4() noexcept
		: glm::vec4(0)
	{
	}

	Vector4::Vector4(float scalar) noexcept
		: glm::vec4(scalar, scalar, scalar, scalar)
	{
	}

	Vector4::Vector4(float x, float y, float z, float w) noexcept
		: glm::vec4(x, y, z, w)
	{
	}

	/*
	Vector4::Vector4() noexcept
		: Vector4(0)
	{
	}

	Vector4::Vector4(float scalar) noexcept
		: Vector4(scalar, scalar, scalar, scalar)
	{
	}

	Vector4::Vector4(float x, float y, float z, float w) noexcept
		: x(x), y(y), z(z), w(w)
	{
	}

	Vector4 Vector4::operator+(const Vector4& other) noexcept
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	Vector4 Vector4::operator-(const Vector4& other) noexcept
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	Vector4 Vector4::operator*(float scalar) noexcept
	{
		return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	Vector4 Vector4::operator/(float scalar) noexcept
	{
		if (scalar != 0)
		{
			float invScalar = 1.0f / scalar;
			return Vector4(x * invScalar, y * invScalar, z * invScalar, w * invScalar);
		}

		return Vector4();
	}

	float Vector4::Length() noexcept
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	void Vector4::Normalize() noexcept
	{
		float length = Length();
		if (length > 0.0f)
		{
			x /= length;
			y /= length;
			z /= length;
			w /= length;
		}
	}
	*/

}