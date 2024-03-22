#pragma once

#include <GLFW/glfw3.h>

#include "Tools/Log.h"
#include "Core/GraphicsEngine/Window.h"

namespace GameEngine
{

	class WindowsWindow : public Window
	{
	private:
		GLFWwindow* window;

	public:
		WindowsWindow(const WindowData& windowData) noexcept;

		virtual ~WindowsWindow() noexcept;

	public:
		void Init() noexcept override;
		void Update() noexcept override;
		void Destroy() noexcept override;

	};

}