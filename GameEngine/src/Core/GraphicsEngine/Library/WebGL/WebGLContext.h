#pragma once

#include <SDL.h>
#include <glad/glad.h>

#include "Core/GraphicsEngine/Library/GraphicsContext.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{

	class WebGLContext : public GraphicsContext
	{
	private:
		SDL_Window* window;

	public:
		WebGLContext(SDL_Window* window) noexcept;

	public:
		void Init() noexcept override;
		void BeginFrame() noexcept override;
		void EndFrame() noexcept override;
		void Destroy() noexcept override;
	};

}