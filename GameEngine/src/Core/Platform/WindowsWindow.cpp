#include "WindowsWindow.h"

namespace GameEngine
{
	WindowsWindow::WindowsWindow(const WindowData& windowData) noexcept
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
			return;
		}
		WINDOW_DEBUG("Initialization GLFW completed");

		WINDOW_DEBUG("Initialization GLFW window has started");
		window = glfwCreateWindow(windowData.Width, windowData.Height, windowData.Title.c_str(), nullptr, nullptr);
		if (!window)
		{
			WINDOW_CRITICAL("GLFW window not initialized!");
			glfwTerminate();
			return;
		}
		glfwSetWindowUserPointer(window, this);
		glfwMaximizeWindow(window);
		glfwMakeContextCurrent(window);
		WINDOW_DEBUG("Initialization GLFW window completed");

		shouldClose = false;

		WINDOW_DEBUG("Initialization GLFW events has started");
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
			{
				EventManager::GetInstance()->GetMouse()->OnMouseMove((float)xPos, (float)yPos);
			}
		);
		WINDOW_TRACE("GLFW mouse events started to be bugged");
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
				{
					EventManager::GetInstance()->GetKetboard()->OnKeyPressed(key);
					break;
				}
				case GLFW_RELEASE:
				{
					EventManager::GetInstance()->GetKetboard()->OnKeyReleased(key);
					break;
				}
				}
			}
		);
		WINDOW_TRACE("GLFW keyboard key events started to be bugged");
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				WindowsWindow* windowsWindow = (WindowsWindow*) glfwGetWindowUserPointer(window);
				windowsWindow->shouldClose = true;
			}
		);
		WINDOW_TRACE("GLFW window close events started to be bugged");
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
		WINDOW_DEBUG("Destruction windows window has started");
		glfwDestroyWindow(window);
		glfwTerminate();
		WINDOW_DEBUG("Destruction windows window completed");
	}

}