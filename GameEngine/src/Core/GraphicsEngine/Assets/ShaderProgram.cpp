#include <fstream>

#include "Core/GraphicsEngine/Assets/ShaderProgram.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

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

	std::string ShaderProgram::ReadShaderCode(const std::string& filepath, const std::string& shaderName)
	{
		GRAPHICS_ENGINE_DEBUG("Shader file [{0}] reading for type [{1}] has started", filepath, shaderName);

		std::string shaderCode;

		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (!in)
		{
			GRAPHICS_ENGINE_CRITICAL("Could not open shader file [{0}]", filepath);
			exit(GameEngine::ASSET_INITIALIZAATION_FAILED);
		}

		in.seekg(0, std::ios::end);
		shaderCode.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&shaderCode[0], shaderCode.size());
		in.close();

		const std::string beginToken = "//begin: " + shaderName;
		const std::string endToken = "//end: " + shaderName;
		size_t beginTokenLength = beginToken.length();
		size_t endTokenLength = endToken.length();
		size_t beginPos = shaderCode.find(beginToken) + beginTokenLength + 2;
		size_t endPos = shaderCode.find(endToken);

		GRAPHICS_ENGINE_DEBUG("Shader file [{0}] reading for type [{1}] completed", filepath, shaderName);

		return shaderCode.substr(beginPos, endPos - beginPos);
	}

}