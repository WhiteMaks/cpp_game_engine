#include "WindowsWindow.h"

namespace GameEngine
{
	WindowsWindow::WindowsWindow(const WindowData& windowData)
		: Window(windowData)
	{
	}

	WindowsWindow::~WindowsWindow()
	{
	}

	void WindowsWindow::Init()
	{
		GAME_ENGINE_DEBUG("Initialization windows window [{0} ({1}, {2})] has started", windowData.Title, windowData.Width, windowData.Height);
		if (!glfwInit())
		{
			GAME_ENGINE_CRITICAL("GLFW not initialized!");
			throw;
		}

		window = glfwCreateWindow(windowData.Width, windowData.Height, windowData.Title.c_str(), glfwGetPrimaryMonitor(), nullptr);
		glfwSetWindowAttrib(window, GLFW_MAXIMIZED, GLFW_TRUE);
		glfwMakeContextCurrent(window);
		GAME_ENGINE_DEBUG("Initialization windows window completed");
	}

	void WindowsWindow::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::Destroy()
	{
		GAME_ENGINE_DEBUG("Destruction windows window has started");
		glfwDestroyWindow(window);
		glfwTerminate();
		GAME_ENGINE_DEBUG("Destruction windows window completed");
	}

}