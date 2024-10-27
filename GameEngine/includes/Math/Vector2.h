#pragma once

#include <glm/glm.hpp>

#include "Core/Core.h"

namespace Math
{

	class GAME_ENGINE_API Vector2 : public glm::vec2
	{

	public:
		Vector2() noexcept;
		Vector2(float scalar) noexcept;
		Vector2(float x, float y) noexcept;

		/*
	public:
		float x;
		float y;


	public:
		Vector2 operator+(const Vector2& other) noexcept;
		Vector2 operator-(const Vector2& other) noexcept;
		Vector2 operator*(float scalar) noexcept;
		Vector2 operator/(float scalar) noexcept;

	public:
		float Length() noexcept;

		void Normalize() noexcept;
		*/
	};

}