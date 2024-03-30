#include "Core/GraphicsEngine/Renderer/GraphicsContextFactory.h"

#include "Core/GraphicsEngine/OpenGL/OpenGLContext.h"
#include "Core/Platform/Windows/WindowsWindow.h"


namespace GraphicsEngine
{

	GraphicsContext* GraphicsContextFactory::Create()
	{
		return new OpenGLContext(Platform::WindowsWindow::window);
	}

}