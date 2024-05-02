#pragma once

#include <glm/glm.hpp>

#include "Core/Core.h"

namespace Math
{

	class GAME_ENGINE_API Vector3 : public glm::vec3
	{
	public:
		float x;
		float y;
		float z;

	public:
		Vector3() noexcept;
		Vector3(float scalar) noexcept;
		Vector3(float x, float y, float z) noexcept;

	public:
		Vector3 operator+(const Vector3& other) noexcept;
		Vector3 operator-(const Vector3& other) noexcept;
		Vector3 operator*(float scalar) noexcept;
		Vector3 operator/(float scalar) noexcept;

	public:
		float Length() noexcept;

		void Normalize() noexcept;
	};

}