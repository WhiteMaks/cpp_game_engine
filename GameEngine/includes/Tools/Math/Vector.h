#pragma once

#include <glm/glm.hpp>

#include "Core/Core.h"

namespace Math
{
	class GAME_ENGINE_API Vector : public glm::vec1
	{
	public:
		Vector(float x) noexcept;
	};
}