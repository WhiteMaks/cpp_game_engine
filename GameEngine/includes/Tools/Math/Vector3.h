#pragma once

#include <glm/glm.hpp>

#include "Core/Core.h"

namespace Math
{

	class GAME_ENGINE_API Vector3 : public glm::vec3
	{
	public:
		Vector3(float scalar) noexcept;
		Vector3(float x, float y, float z) noexcept;

	};

}