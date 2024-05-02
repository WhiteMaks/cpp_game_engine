#pragma once

#include <glm/glm.hpp>

#include "Core/Core.h"

namespace Math
{

	class GAME_ENGINE_API Vector4 : public glm::vec4
	{
	public:
		Vector4() noexcept;
		Vector4(float scalar) noexcept;
		Vector4(float x, float y, float z, float w) noexcept;

		/*
	public:
		float x;
		float y;
		float z;
		float w;

	public:
		Vector4() noexcept;
		Vector4(float scalar) noexcept;
		Vector4(float x, float y, float z, float w) noexcept;

	public:
		Vector4 operator+(const Vector4& other) noexcept;
		Vector4 operator-(const Vector4& other) noexcept;
		Vector4 operator*(float scalar) noexcept;
		Vector4 operator/(float scalar) noexcept;

	public:
		float Length() noexcept;

		void Normalize() noexcept;
		*/
	};

}