#pragma once

#include <SDL.h>
#include <glad/glad.h>

#include "Core/GraphicsEngine/Renderer/GraphicsContext.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

#include "WebGLShaderProgram.h"

namespace GraphicsEngine
{

	class WebGLContext : public GraphicsContext
	{
	private:
		SDL_Window* window;

		unsigned int vertexArray, vertexBuffer, indexBuffer;
		std::unique_ptr<ShaderProgram> shaderProgram;

	public:
		WebGLContext(SDL_Window* window) noexcept;

	public:
		void Init() noexcept override;
		void SwapBuffers() noexcept override;
		void Destroy() noexcept override;
	};

}