#include "Core/GraphicsEngine/WindowFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
	#include "Core/GraphicsEngine/GraphicsEngine.h"
	#include "Core/Platform/Browser/BrowserWindow.h"
	#include "Core/Platform/Windows/WindowsWindow.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
	#include "Core/Platform/Browser/BrowserWindow.h"
#endif

namespace GraphicsEngine
{

	Window* WindowFactory::Create(const WindowData& windowData)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return new Platform::BrowserWindow(windowData);
		case GraphicsAPI::OpenGL: 
		case GraphicsAPI::DirectX_11: 
		case GraphicsAPI::DirectX_12: return new Platform::WindowsWindow(windowData);
		default: throw;
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return new Platform::BrowserWindow(windowData);
#else
	#error Window only supports Windows and Browser!
#endif
	}

}