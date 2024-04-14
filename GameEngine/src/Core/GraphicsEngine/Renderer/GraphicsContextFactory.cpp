#include "Core/GraphicsEngine/Renderer/GraphicsContextFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#include "Core/Platform/Browser/BrowserWindow.h"
#include "Core/GraphicsEngine/WebGL/WebGLContext.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLContext.h"
#include "Core/GraphicsEngine/DirectX/DirectX11Context.h"
#include "Core/GraphicsEngine/DirectX/DirectX12Context.h"
#include "Core/GraphicsEngine/GraphicsEngine.h"
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
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return new WebGLContext(Platform::BrowserWindow::window);
		case GraphicsAPI::OpenGL: return new OpenGLContext(Platform::WindowsWindow::window);
		case GraphicsAPI::DirectX_11: return new DirectX11Context(Platform::WindowsWindow::window);
		case GraphicsAPI::DirectX_12: return new DirectX12Context(Platform::WindowsWindow::window);
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return new WebGLContext(Platform::BrowserWindow::window);
#else
#error Graphics context only supports Windows and Browser!
#endif
		return new GraphicsContext();
	}

}