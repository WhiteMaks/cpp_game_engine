#pragma once

#include <SDL.h>
#include <glad/glad.h>

#include "Core/GraphicsEngine/Renderer/GraphicsContext.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

#include "WebGLShaderProgram.h"
#include "WebGLVertexArrayBuffer.h"
#include "WebGLVertexStaticBuffer.h"
#include "WebGLIndexStaticBuffer.h"

namespace GraphicsEngine
{

	class WebGLContext : public GraphicsContext
	{
	private:
		SDL_Window* window;

		std::shared_ptr<ShaderProgram> shaderProgram;
		std::shared_ptr<VertexArrayBuffer> vertexArrayBuffer;

	public:
		WebGLContext(SDL_Window* window) noexcept;

	public:
		void Init() noexcept override;
		void BeginFrame() noexcept override;
		void EndFrame() noexcept override;
		void Destroy() noexcept override;
	};

}