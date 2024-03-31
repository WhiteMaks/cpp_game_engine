#pragma once

#include <SDL.h>
#include <SDL_opengles2.h>

#include "Core/GraphicsEngine/Renderer/GraphicsContext.h"
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
		void SwapBuffers() noexcept override;
		void Destroy() noexcept override;
	};

}