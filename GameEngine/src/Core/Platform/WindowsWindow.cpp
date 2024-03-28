#include "WindowsWindow.h"
#include "ExitCodes.h"

namespace Platform
{
	WindowsWindow::WindowsWindow(const GraphicsEngine::WindowData& windowData) noexcept
		: Window(windowData), window(nullptr)
	{
	}

	WindowsWindow::~WindowsWindow() noexcept
	{
	}

	void WindowsWindow::Init() noexcept
	{
		WINDOW_INFO("Initialization windows window [{0} ({1}, {2})] has started", windowData.Title, windowData.Width, windowData.Height);
		
		WINDOW_DEBUG("Initialization GLFW has started");
		if (!glfwInit())
		{
			WINDOW_CRITICAL("GLFW not initialized!");
			exit(GameEngine::WINDOW_INITIALIZAATION_FAILED);
		}
		WINDOW_DEBUG("Initialization GLFW completed");

		WINDOW_DEBUG("Initialization GLFW window has started");
		window = glfwCreateWindow(
			windowData.Width, windowData.Height, 
			windowData.Title.c_str(), 
			nullptr, nullptr
		);

		if (!window)
		{
			WINDOW_CRITICAL("GLFW window not initialized!");
			glfwTerminate();
			exit(GameEngine::WINDOW_INITIALIZAATION_FAILED);
		}
		glfwMaximizeWindow(window);
		glfwMakeContextCurrent(window);
		WINDOW_DEBUG("Initialization GLFW window completed");

		shouldClose = false;

		WINDOW_DEBUG("Initialization GLFW events has started");
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
			{
				EventsSystem::EventManager::GetInstance()->GetMouse()->OnMouseMove((float) xPos, (float) yPos);
			}
		);
		WINDOW_TRACE("GLFW mouse events started to be bugged");
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
		WINDOW_TRACE("GLFW keyboard key events started to be bugged");
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				EventsSystem::EventManager::GetInstance()->GetWindow()->OnClose();
			}
		);
		WINDOW_TRACE("GLFW window close events started to be bugged");
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				EventsSystem::EventManager::GetInstance()->GetWindow()->OnResize(width, height);
			}
		);
		WINDOW_TRACE("GLFW window resize events started to be bugged");
		WINDOW_DEBUG("Initialization GLFW events completed");

		WINDOW_INFO("Initialization windows window completed");
	}

	void WindowsWindow::Update() noexcept
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::Destroy() noexcept
	{
		WINDOW_INFO("Destruction windows window has started");

		glfwDestroyWindow(window);
		WINDOW_TRACE("GLFW window destroyed");
		glfwTerminate();
		WINDOW_TRACE("GLFW terminated");

		WINDOW_INFO("Destruction windows window completed");
	}

}