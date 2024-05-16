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

	void ShaderProgram::SetUniformInt(const std::string& uniformName, int value) noexcept
	{
	}

	void ShaderProgram::SetUniformFloat(const std::string& uniformName, float value) noexcept
	{
	}

	void ShaderProgram::SetUniformFloat2(const std::string& uniformName, Math::Vector2 vector) noexcept
	{
	}

	void ShaderProgram::SetUniformFloat3(const std::string& uniformName, Math::Vector3 vector) noexcept
	{
	}

	void ShaderProgram::SetUniformFloat4(const std::string& uniformName, Math::Vector4 vector) noexcept
	{
	}

	void ShaderProgram::SetUniformMat3(const std::string& uniformName, glm::mat3 matrix) noexcept
	{
	}

	void ShaderProgram::SetUniformMat4(const std::string& uniformName, glm::mat4 matrix) noexcept
	{
	}

	void ShaderProgram::Destroy() noexcept
	{
	}

}