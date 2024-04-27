#include "Tools/Math/Vector3.h"

namespace Math
{

	Vector3::Vector3(float scalar) noexcept
		: vec(scalar)
	{
	}

	Vector3::Vector3(float x, float y, float z) noexcept
		: vec(x, y, z)
	{
	}

}