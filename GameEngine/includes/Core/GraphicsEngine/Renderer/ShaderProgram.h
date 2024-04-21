#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GraphicsEngine
{

	class ShaderProgram
	{
	protected:
		const std::string& vertexShaderCode;
		const std::string& fragmentShaderCode;

	public:
		ShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) noexcept;

	public:
		virtual void Init() noexcept;

		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;

		virtual void SetUniformMat4(const std::string& uniformName, glm::mat4 matrix) noexcept;

		virtual void Destroy() noexcept;
	
	};

}