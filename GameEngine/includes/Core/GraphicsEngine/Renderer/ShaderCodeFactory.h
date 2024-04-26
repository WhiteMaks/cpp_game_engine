#pragma once

#include <string>

#include "Core/Core.h"
#include "Core/GraphicsEngine/GraphicsEngine.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API ShaderCodeFactory
	{
	public:
		static std::string CreateDefaultVertexShader();
		static std::string CreateDefaultFragmentShader();
	};

}