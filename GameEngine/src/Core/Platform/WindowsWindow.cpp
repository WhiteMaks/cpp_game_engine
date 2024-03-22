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
		GAME_ENGINE_DEBUG("Initialization windows window [{0} ({1}, {2})] has started", windowData.Title, windowData.Width, windowData.Height);
		
		GAME_ENGINE_TRACE("Initialization GLFW has started");
		if (!glfwInit())
		{
			GAME_ENGINE_CRITICAL("GLFW not initialized!");
			throw;
		}
		GAME_ENGINE_TRACE("Initialization GLFW completed");

		GAME_ENGINE_TRACE("Initialization GLFW window has started");
		window = glfwCreateWindow(windowData.Width, windowData.Height, windowData.Title.c_str(), nullptr, nullptr);
		if (!window)
		{
			GAME_ENGINE_CRITICAL("GLFW window not initialized!");
			glfwTerminate();
			throw;
		}
		glfwMaximizeWindow(window);
		glfwMakeContextCurrent(window);
		GAME_ENGINE_TRACE("Initialization GLFW window completed");

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