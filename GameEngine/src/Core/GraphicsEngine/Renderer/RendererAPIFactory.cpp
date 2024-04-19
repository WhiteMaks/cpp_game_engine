#include "Core/GraphicsEngine/Renderer/RendererAPIFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#include "Core/GraphicsEngine/GraphicsEngine.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLRenderer.h"
#include "Core/GraphicsEngine/WebGL/WebGLRenderer.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
#endif

namespace GraphicsEngine
{

	RendererAPI* RendererAPIFactory::Create()
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return new WebGLRenderer();
		case GraphicsAPI::OpenGL: return new OpenGLRenderer();
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return new WebGLRenderer();
#endif
		return new RendererAPI();
	}

}