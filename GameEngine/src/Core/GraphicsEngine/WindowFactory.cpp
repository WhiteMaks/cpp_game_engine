#include "Core/GraphicsEngine/WindowFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
	#include "Core/Platform/WindowsWindow.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
	#include "Core/Platform/BrowserWindow.h"
#endif

namespace GameEngine
{

	Window* WindowFactory::Create(const WindowData& windowData)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		return new WindowsWindow(windowData);
#elif GAME_ENGINE_PLATFORM_BROWSER
		return nullptr;
#else
	#error Window only supports Windows and Browser!
#endif
	}

}