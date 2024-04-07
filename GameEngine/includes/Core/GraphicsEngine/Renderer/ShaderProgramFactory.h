#pragma once

#include "ShaderProgram.h"

namespace GraphicsEngine
{

	class ShaderProgramFactory
	{
	public:
		static ShaderProgram* Create(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
	};

}