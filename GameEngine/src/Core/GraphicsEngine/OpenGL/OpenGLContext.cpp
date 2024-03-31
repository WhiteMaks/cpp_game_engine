#include "OpenGLContext.h"

namespace GraphicsEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* window) noexcept
		: window(window)
	{
		if (!window)
		{
			GRAPHICS_ENGINE_CRITICAL("GLFW window is null!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}
	}

	void OpenGLContext::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization openGL context has started");

		GRAPHICS_ENGINE_DEBUG("Initialization GLAD has started");
		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			GRAPHICS_ENGINE_CRITICAL("GLAD not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization GLAD completed");

		GRAPHICS_ENGINE_INFO("Initialization openGL context completed");
	}

	void OpenGLContext::SwapBuffers() noexcept
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 1, 1);
		glfwSwapBuffers(window);
	}

	void OpenGLContext::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction openGL context has started");
		GRAPHICS_ENGINE_INFO("Destruction openGL context completed");
	}

}