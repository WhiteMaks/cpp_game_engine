#include "WindowsWindow.h"

namespace GameEngine
{
	WindowsWindow::WindowsWindow(const WindowData& windowData)
		: Window(windowData), window(nullptr)
	{
	}

	WindowsWindow::~WindowsWindow()
	{
	}

	void WindowsWindow::Init()
	{
		WINDOW_DEBUG("Initialization windows window [{0} ({1}, {2})] has started", windowData.Title, windowData.Width, windowData.Height);
		
		WINDOW_TRACE("Initialization GLFW has started");
		if (!glfwInit())
		{
			WINDOW_CRITICAL("GLFW not initialized!");
			throw;
		}
		WINDOW_TRACE("Initialization GLFW completed");

		WINDOW_TRACE("Initialization GLFW window has started");
		window = glfwCreateWindow(windowData.Width, windowData.Height, windowData.Title.c_str(), nullptr, nullptr);
		if (!window)
		{
			WINDOW_CRITICAL("GLFW window not initialized!");
			glfwTerminate();
			throw;
		}
		glfwMaximizeWindow(window);
		glfwMakeContextCurrent(window);
		WINDOW_TRACE("Initialization GLFW window completed");

		WINDOW_DEBUG("Initialization windows window completed");
	}

	void WindowsWindow::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::Destroy()
	{
		WINDOW_DEBUG("Destruction windows window has started");
		glfwDestroyWindow(window);
		glfwTerminate();
		WINDOW_DEBUG("Destruction windows window completed");
	}

}