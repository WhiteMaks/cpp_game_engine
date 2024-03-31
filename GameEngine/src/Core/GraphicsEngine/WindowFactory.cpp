#include "Core/GraphicsEngine/WindowFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
	#include "Core/Platform/Windows/WindowsWindow.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
	#include "Core/Platform/Browser/BrowserWindow.h"
#endif

namespace GraphicsEngine
{

	Window* WindowFactory::Create(const WindowData& windowData)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		return new Platform::WindowsWindow(windowData);
#elif GAME_ENGINE_PLATFORM_BROWSER
		return new Platform::BrowserWindow(windowData);
#else
	#error Window only supports Windows and Browser!
#endif
	}

}