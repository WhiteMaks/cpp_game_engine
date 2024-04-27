#include "Tools/Math/Vector2.h"

namespace Math
{

	Vector2::Vector2(float scalar) noexcept
		: vec(scalar)
	{
	}

	Vector2::Vector2(float x, float y) noexcept
		: vec(x, y)
	{
	}

}