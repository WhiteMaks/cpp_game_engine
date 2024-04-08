#pragma once

#include <string>

namespace GraphicsEngine
{

	class ShaderProgram
	{
	protected:
		const std::string& vertexShaderCode;
		const std::string& fragmentShaderCode;

	protected:
		ShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) noexcept;

	public:
		virtual void Init() noexcept;

		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;

		virtual void Destroy() noexcept;
	
	};

}