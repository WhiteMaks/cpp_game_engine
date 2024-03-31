#pragma once

#include <GLFW/glfw3.h>

#include "Core/GraphicsEngine/Window.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace Platform
{

	class WindowsWindow : public GraphicsEngine::Window
	{
	public:
		static GLFWwindow* window;

	public:
		WindowsWindow(const GraphicsEngine::WindowData& windowData) noexcept;

		virtual ~WindowsWindow() noexcept;

	public:
		void Init() noexcept override;
		void Update() noexcept override;
		void Destroy() noexcept override;

	};

}