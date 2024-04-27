#pragma once

#include <glm/glm.hpp>

#include "Core/Core.h"

namespace Math
{

	class GAME_ENGINE_API Vector2 : public glm::vec2
	{
	public:
		Vector2(float scalar) noexcept;
		Vector2(float x, float y) noexcept;

	};

}