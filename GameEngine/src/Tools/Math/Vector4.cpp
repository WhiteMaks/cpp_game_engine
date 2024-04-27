#include "Tools/Math/Vector4.h"

namespace Math
{

	Vector4::Vector4(float scalar) noexcept
		: vec(scalar)
	{
	}

	Vector4::Vector4(float x, float y, float z, float w) noexcept
		: vec(x, y, z, w)
	{
	}

}