#pragma once

#include <glad/glad.h>
#include <Windows.h>
#include <iostream>

#include "Core/GraphicsEngine/Renderer/GraphicsContext.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

#include "OpenGLShaderProgram.h"
#include "OpenGLVertexStaticBuffer.h"
#include "OpenGLIndexStaticBuffer.h"
#include "OpenGLVertexArrayBuffer.h"
#include "Core/GraphicsEngine/Renderer/BufferLayout.h"

namespace GraphicsEngine
{

	class OpenGLContext : public GraphicsContext
	{
	private:
		HWND window;
		HDC hdc;
		HGLRC hglrc;

		std::shared_ptr<ShaderProgram> shaderProgram;
		std::shared_ptr<VertexArrayBuffer> vertexArrayBuffer;

	public:
		OpenGLContext(HWND window) noexcept;

	public:
		void Init() noexcept override;
		void BeginFrame() noexcept override;
		void EndFrame() noexcept override;
		void Destroy() noexcept override;
	};

}