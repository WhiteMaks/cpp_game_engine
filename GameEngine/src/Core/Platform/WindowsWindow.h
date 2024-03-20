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
		WindowsWindow(const WindowData& windowData);

		virtual ~WindowsWindow();

	public:
		void Init() override;
		void Update() override;
		void Destroy() override;

	};

}