#pragma once

#include "Core/Core.h"

namespace Math
{
	class GAME_ENGINE_API Vector
	{
	public:
		float x;

	public:
		Vector() noexcept;
		Vector(float x) noexcept;

	public:
		Vector operator+(const Vector& other) noexcept;
		Vector operator-(const Vector& other) noexcept;
		Vector operator*(float scalar) noexcept;
		Vector operator/(float scalar) noexcept;

	public:
		float Length() noexcept;

		void Normalize() noexcept;
	};
}