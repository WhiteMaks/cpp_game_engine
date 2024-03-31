#include "Core/GraphicsEngine/Renderer/GraphicsContextFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#include "Core/GraphicsEngine/OpenGL/OpenGLContext.h"
#include "Core/Platform/Windows/WindowsWindow.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
#include "Core/Platform/Browser/BrowserWindow.h"
#include "Core/GraphicsEngine/WebGL/WebGLContext.h"
#endif

namespace GraphicsEngine
{

	GraphicsContext* GraphicsContextFactory::Create()
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		return new OpenGLContext(Platform::WindowsWindow::window);
#elif GAME_ENGINE_PLATFORM_BROWSER
		return new WebGLContext(Platform::BrowserWindow::window);
#else
#error Graphics context only supports Windows and Browser!
#endif
	}

}