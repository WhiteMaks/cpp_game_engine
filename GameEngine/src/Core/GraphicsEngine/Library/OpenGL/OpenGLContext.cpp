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

		glfwMakeContextCurrent(window);

		GRAPHICS_ENGINE_DEBUG("Initialization GLAD has started");
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			GRAPHICS_ENGINE_CRITICAL("GLAD not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization GLAD completed");

		GRAPHICS_ENGINE_TRACE("OpenGL version [{0}]", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		GRAPHICS_ENGINE_TRACE("Selected GPU adapter [{0}]", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));

		GRAPHICS_ENGINE_INFO("Initialization openGL context completed");
	}

	void OpenGLContext::BeginFrame() noexcept
	{
	}

	void OpenGLContext::EndFrame() noexcept
	{
		glfwSwapBuffers(window);
	}

	void OpenGLContext::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction openGL context has started");
		GRAPHICS_ENGINE_INFO("Destruction openGL context completed");
	}

}