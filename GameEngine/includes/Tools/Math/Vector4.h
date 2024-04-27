#pragma once

#include <glm/glm.hpp>

#include "Core/Core.h"

namespace Math
{

	class GAME_ENGINE_API Vector4 : public glm::vec4
	{
	public:
		Vector4(float scalar) noexcept;
		Vector4(float x, float y, float z, float w) noexcept;

	};

}