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
		



		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	void WebGLContext::SwapBuffers() noexcept
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 1, 1);

		glBindVertexArray(vertexArray);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_GL_SwapWindow(window);
	}

	void WebGLContext::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction webGL context has started");
		GRAPHICS_ENGINE_INFO("Destruction webGL context completed");
	}

}