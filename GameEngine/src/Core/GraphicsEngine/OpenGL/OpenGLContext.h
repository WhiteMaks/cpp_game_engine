#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/GraphicsEngine/Renderer/GraphicsContext.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{

	class OpenGLContext : public GraphicsContext
	{
	private:
		GLFWwindow* window;

	public:
		OpenGLContext(GLFWwindow* window) noexcept;

	public:
		void Init() noexcept override;
		void SwapBuffers() noexcept override;
		void Destroy() noexcept override;
	};

}