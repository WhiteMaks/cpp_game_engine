#pragma once

#include <glad/glad.h>

#include "Core/GraphicsEngine/Assets/ShaderProgram.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{

	class WebGLShaderProgram : public ShaderProgram
	{
	private:
		GLuint shaderProgram;
		GLuint vertexShader;
		GLuint fragmentShader;

	public:
		WebGLShaderProgram(const std::string& filepath) noexcept;
		WebGLShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) noexcept;

	public:
		void Init() noexcept override;
		void Bind() noexcept override;
		void Unbind() noexcept override;
		void Destroy() noexcept override;

		void SetUniformFloat(const std::string& uniformName, float value) noexcept override;
		void SetUniformFloat2(const std::string& uniformName, Math::Vector2 vector) noexcept override;
		void SetUniformFloat3(const std::string& uniformName, Math::Vector3 vector) noexcept override;
		void SetUniformFloat4(const std::string& uniformName, Math::Vector4 vector) noexcept override;
		void SetUniformMat3(const std::string& uniformName, glm::mat3 matrix) noexcept override;
		void SetUniformMat4(const std::string& uniformName, glm::mat4 matrix) noexcept override;

	private:
		void InitShaderProgram() noexcept;
		void InitShaders() noexcept;

		std::string ReadVertexShaderCode(const std::string& filepath);
		std::string ReadFragmentShaderCode(const std::string& filepath);
	};

}