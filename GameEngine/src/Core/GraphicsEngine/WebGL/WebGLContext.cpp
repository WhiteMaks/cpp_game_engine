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

		GRAPHICS_ENGINE_DEBUG("Initialization GLAD has started");
		if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
		{
			GRAPHICS_ENGINE_CRITICAL("GLAD not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization GLAD completed");

		GRAPHICS_ENGINE_TRACE("OpenGL version [{0}]", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		GRAPHICS_ENGINE_TRACE("Selected GPU adapter [{0}]", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));

		GRAPHICS_ENGINE_INFO("Initialization webGL context completed");
	}

	void WebGLContext::BeginFrame() noexcept
	{
	}

	void WebGLContext::EndFrame() noexcept
	{
		SDL_GL_SwapWindow(window);
	}

	void WebGLContext::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction webGL context has started");
		GRAPHICS_ENGINE_INFO("Destruction webGL context completed");
	}

}