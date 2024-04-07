#pragma once

#include <glad/glad.h>
#include <Windows.h>
#include <iostream>

#include "Core/GraphicsEngine/Renderer/GraphicsContext.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

#include "OpenGLShaderProgram.h"

namespace GraphicsEngine
{

	class OpenGLContext : public GraphicsContext
	{
	private:
		HWND window;
		HDC hdc;
		HGLRC hglrc;

		unsigned int vertexArray, vertexBuffer, indexBuffer;
		std::unique_ptr<ShaderProgram> shaderProgram;

	public:
		OpenGLContext(HWND window) noexcept;

	public:
		void Init() noexcept override;
		void SwapBuffers() noexcept override;
		void Destroy() noexcept override;
	};

}