#pragma once

#include <string>

#include "Core/GraphicsEngine/GraphicsEngine.h"

namespace GraphicsEngine
{

	class ShaderCodeFactory
	{
	public:
		static std::string CreateDefaultVertexShader();
		static std::string CreateDefaultFragmentShader();
	};

}