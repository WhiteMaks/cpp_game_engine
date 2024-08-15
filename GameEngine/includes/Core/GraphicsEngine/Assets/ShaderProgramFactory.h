#pragma once

#include <memory>

#include "Core/Core.h"
#include "ShaderProgram.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API ShaderProgramFactory
	{
	public:
		static std::shared_ptr<ShaderProgram> Create(const std::string& filepath);
		static std::shared_ptr<ShaderProgram> Create(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
	};

}