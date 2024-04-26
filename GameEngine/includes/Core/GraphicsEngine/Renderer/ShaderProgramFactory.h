#pragma once

#include "Core/Core.h"
#include "ShaderProgram.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API ShaderProgramFactory
	{
	public:
		static ShaderProgram* Create(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
	};

}