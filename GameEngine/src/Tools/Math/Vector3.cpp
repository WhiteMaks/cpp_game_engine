#include <cmath>

#include "Tools/Math/Vector3.h"

namespace Math
{
	Vector3::Vector3() noexcept
		: glm::vec3(0.0f)
	{
	}

	Vector3::Vector3(float scalar) noexcept
		: glm::vec3(scalar, scalar, scalar)
	{
	}

	Vector3::Vector3(float x, float y, float z) noexcept
		: glm::vec3(x, y, z)
	{
	}

	/*
	Vector3::Vector3() noexcept
		: Vector3(0.0f)
	{
	}

	Vector3::Vector3(float scalar) noexcept
		: Vector3(scalar, scalar, scalar)
	{
	}

	Vector3::Vector3(float x, float y, float z) noexcept
		: x(x), y(y), z(z)
	{
	}

	Vector3 Vector3::operator+(const Vector3& other) noexcept
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 Vector3::operator-(const Vector3& other) noexcept
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	Vector3 Vector3::operator*(float scalar) noexcept
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	Vector3 Vector3::operator/(float scalar) noexcept
	{
		if (scalar != 0)
		{
			float invScalar = 1.0f / scalar;
			return Vector3(x * invScalar, y * invScalar, z * invScalar);
		}

		return Vector3();
	}

	float Vector3::Length() noexcept
	{
		return sqrt(x * x + y * y + z * z);
	}

	void Vector3::Normalize() noexcept
	{
		float length = Length();
		if (length > 0.0f)
		{
			x /= length;
			y /= length;
			z /= length;
		}
	}
	*/
}