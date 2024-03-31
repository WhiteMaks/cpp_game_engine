#include "WebGLContext.h"

namespace GraphicsEngine
{
	WebGLContext::WebGLContext(SDL_Window* window) noexcept
		: window(window)
	{
		if (!window)
		{
			GRAPHICS_ENGINE_CRITICAL("SDL window is null!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}
	}

	void WebGLContext::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization webGL context has started");
		SDL_GL_CreateContext(window);
		GRAPHICS_ENGINE_INFO("Initialization webGL context completed");
	}

	void WebGLContext::SwapBuffers() noexcept
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 1, 1);
		SDL_GL_SwapWindow(window);
	}

	void WebGLContext::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction webGL context has started");
		GRAPHICS_ENGINE_INFO("Destruction webGL context completed");
	}

}