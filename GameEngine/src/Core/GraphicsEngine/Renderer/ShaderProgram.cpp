#include "Core/GraphicsEngine/Renderer/ShaderProgram.h"

namespace GraphicsEngine
{

	ShaderProgram::ShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) noexcept
		: vertexShaderCode(vertexShaderCode), fragmentShaderCode(fragmentShaderCode)
	{
	}

	void ShaderProgram::Init() noexcept
	{
	}

	void ShaderProgram::Bind() noexcept
	{
	}

	void ShaderProgram::Unbind() noexcept
	{
	}

	void ShaderProgram::Destroy() noexcept
	{
	}

}