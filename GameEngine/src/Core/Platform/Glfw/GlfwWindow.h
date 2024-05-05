#pragma once

#include <GLFW/glfw3.h>

#include "Core/GraphicsEngine/Window.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace Platform
{

	class GlfwWindow : public GraphicsEngine::Window
	{
	public:
		static GLFWwindow* window;

	public:
		GlfwWindow(const GraphicsEngine::WindowData& windowData) noexcept;

	public:
		void Init() noexcept override;
		void Update() noexcept override;
		void Destroy() noexcept override;

	};

}