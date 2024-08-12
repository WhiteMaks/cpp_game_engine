#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tools/Math/Vector2.h"
#include "Tools/Math/Vector3.h"
#include "Tools/Math/Vector4.h"

namespace GraphicsEngine
{

	class ShaderProgram
	{
	protected:
		std::string vertexShaderCode;
		std::string fragmentShaderCode;

	public:
		ShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) noexcept;

	public:
		virtual void Init() noexcept;

		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;

		virtual void SetUniformInt(const std::string& uniformName, int value) noexcept;
		virtual void SetUniformFloat(const std::string& uniformName, float value) noexcept;
		virtual void SetUniformFloat2(const std::string& uniformName, Math::Vector2 vector) noexcept;
		virtual void SetUniformFloat3(const std::string& uniformName, Math::Vector3 vector) noexcept;
		virtual void SetUniformFloat4(const std::string& uniformName, Math::Vector4 vector) noexcept;
		virtual void SetUniformMat3(const std::string& uniformName, glm::mat3 matrix) noexcept;
		virtual void SetUniformMat4(const std::string& uniformName, glm::mat4 matrix) noexcept;

		virtual void Destroy() noexcept;

	protected:
		std::string ReadShaderCode(const std::string& filepath, const std::string& shaderName);

	};

}