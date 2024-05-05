#include "GlfwWindow.h"

namespace Platform
{
	GLFWwindow* GlfwWindow::window;

	GlfwWindow::GlfwWindow(const GraphicsEngine::WindowData& windowData) noexcept
		: Window(windowData)
	{
	}

	void GlfwWindow::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization glfw window [{0}] has started", windowData.Title);

		GRAPHICS_ENGINE_DEBUG("Initialization GLFW has started");
		if (!glfwInit())
		{
			GRAPHICS_ENGINE_CRITICAL("GLFW not initialized!");
			exit(GameEngine::WINDOW_INITIALIZAATION_FAILED);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization GLFW completed");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
				EventsSystem::EventManager::GetInstance()->GetMouse()->OnMouseMove((float)xPos, (float)yPos);
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

		EventsSystem::EventManager::keyA = 65;
		EventsSystem::EventManager::keyB = 66;
		EventsSystem::EventManager::keyC = 67;
		EventsSystem::EventManager::keyD = 68;
		EventsSystem::EventManager::keyE = 69;
		EventsSystem::EventManager::keyF = 70;
		EventsSystem::EventManager::keyG = 71;
		EventsSystem::EventManager::keyH = 72;
		EventsSystem::EventManager::keyI = 73;
		EventsSystem::EventManager::keyJ = 74;
		EventsSystem::EventManager::keyK = 75;
		EventsSystem::EventManager::keyL = 76;
		EventsSystem::EventManager::keyM = 77;
		EventsSystem::EventManager::keyN = 78;
		EventsSystem::EventManager::keyO = 79;
		EventsSystem::EventManager::keyP = 80;
		EventsSystem::EventManager::keyQ = 81;
		EventsSystem::EventManager::keyR = 82;
		EventsSystem::EventManager::keyS = 83;
		EventsSystem::EventManager::keyT = 84;
		EventsSystem::EventManager::keyU = 85;
		EventsSystem::EventManager::keyV = 86;
		EventsSystem::EventManager::keyW = 87;
		EventsSystem::EventManager::keyX = 88;
		EventsSystem::EventManager::keyY = 89;
		EventsSystem::EventManager::keyZ = 90;

		GRAPHICS_ENGINE_INFO("Initialization glfw window completed");
	}

	void GlfwWindow::Update() noexcept
	{
		glfwPollEvents();
	}

	void GlfwWindow::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction glfw window has started");

		glfwDestroyWindow(window);
		GRAPHICS_ENGINE_TRACE("GLFW window destroyed");
		glfwTerminate();
		GRAPHICS_ENGINE_TRACE("GLFW terminated");

		GRAPHICS_ENGINE_INFO("Destruction glfw window completed");
	}

}