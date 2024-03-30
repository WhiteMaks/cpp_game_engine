#include "WindowsWindow.h"

namespace Platform
{
	GLFWwindow* WindowsWindow::window;

	WindowsWindow::WindowsWindow(const GraphicsEngine::WindowData& windowData) noexcept
		: Window(windowData)
	{
	}

	WindowsWindow::~WindowsWindow() noexcept
	{
	}

	void WindowsWindow::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization windows window [{0} ({1}, {2})] has started", windowData.Title, windowData.Width, windowData.Height);
		
		GRAPHICS_ENGINE_DEBUG("Initialization GLFW has started");
		if (!glfwInit())
		{
			GRAPHICS_ENGINE_CRITICAL("GLFW not initialized!");
			exit(GameEngine::WINDOW_INITIALIZAATION_FAILED);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization GLFW completed");

		GRAPHICS_ENGINE_DEBUG("Initialization GLFW window has started");
		window = glfwCreateWindow(
			windowData.Width, windowData.Height, 
			windowData.Title.c_str(), 
			nullptr, nullptr
		);

		if (!window)
		{
			GRAPHICS_ENGINE_CRITICAL("GLFW window not initialized!");
			glfwTerminate();
			exit(GameEngine::WINDOW_INITIALIZAATION_FAILED);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization GLFW window completed");

		shouldClose = false;

		GRAPHICS_ENGINE_DEBUG("Initialization GLFW events has started");
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
			{
				EventsSystem::EventManager::GetInstance()->GetMouse()->OnMouseMove((float) xPos, (float) yPos);
			}
		);
		GRAPHICS_ENGINE_TRACE("GLFW mouse events started to be bugged");
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
				{
					EventsSystem::EventManager::GetInstance()->GetKetboard()->OnKeyPressed(key);
					break;
				}
				case GLFW_RELEASE:
				{
					EventsSystem::EventManager::GetInstance()->GetKetboard()->OnKeyReleased(key);
					break;
				}
				}
			}
		);
		GRAPHICS_ENGINE_TRACE("GLFW keyboard key events started to be bugged");
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				EventsSystem::EventManager::GetInstance()->GetWindow()->OnClose();
			}
		);
		GRAPHICS_ENGINE_TRACE("GLFW window close events started to be bugged");
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				EventsSystem::EventManager::GetInstance()->GetWindow()->OnResize(width, height);
			}
		);
		GRAPHICS_ENGINE_TRACE("GLFW window resize events started to be bugged");
		GRAPHICS_ENGINE_DEBUG("Initialization GLFW events completed");

		glfwMaximizeWindow(window);

		GRAPHICS_ENGINE_INFO("Initialization windows window completed");
	}

	void WindowsWindow::Update() noexcept
	{
		glfwPollEvents();
	}

	void WindowsWindow::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction windows window has started");

		glfwDestroyWindow(window);
		GRAPHICS_ENGINE_TRACE("GLFW window destroyed");
		glfwTerminate();
		GRAPHICS_ENGINE_TRACE("GLFW terminated");

		GRAPHICS_ENGINE_INFO("Destruction windows window completed");
	}

}