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
#include "Core/GraphicsEngine/Renderer/BufferLayout.h"

namespace GraphicsEngine
{

	class OpenGLContext : public GraphicsContext
	{
	private:
		HWND window;
		HDC hdc;
		HGLRC hglrc;

		unsigned int vertexArray;
		std::unique_ptr<ShaderProgram> shaderProgram;
		std::unique_ptr<VertexStaticBuffer> vertexBuffer;
		std::unique_ptr<IndexStaticBuffer> indexBuffer;

	public:
		OpenGLContext(HWND window) noexcept;

	public:
		void Init() noexcept override;
		void StartFrame() noexcept override;
		void EndFrame() noexcept override;
		void Destroy() noexcept override;
	};

}