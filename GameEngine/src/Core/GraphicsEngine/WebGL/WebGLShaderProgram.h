#pragma once

#include <glad/glad.h>

#include "Core/GraphicsEngine/Renderer/ShaderProgram.h"
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
		WebGLShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) noexcept;

	public:
		void Init() noexcept override;
		void Bind() noexcept override;
		void Unbind() noexcept override;
		void Destroy() noexcept override;

		void SetUniformMat4(const std::string& uniformName, glm::mat4 matrix) noexcept override;

	private:
		void InitShaderProgram() noexcept;
		void InitShaders() noexcept;
	};

}