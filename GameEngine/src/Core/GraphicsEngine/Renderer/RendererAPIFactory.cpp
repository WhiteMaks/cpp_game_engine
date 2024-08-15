#include "Core/GraphicsEngine/Renderer/RendererAPIFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#include "Core/GraphicsEngine/GraphicsEngine.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLRenderer.h"
#include "Core/GraphicsEngine/WebGL/WebGLRenderer.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
#include "Core/GraphicsEngine/WebGL/WebGLRenderer.h"
#endif

namespace GraphicsEngine
{

	std::unique_ptr<RendererAPI> RendererAPIFactory::Create()
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return std::unique_ptr<RendererAPI>(new WebGLRenderer());
		case GraphicsAPI::OpenGL: return std::unique_ptr<RendererAPI>(new OpenGLRenderer());
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return std::unique_ptr<RendererAPI>(new WebGLRenderer());
#endif
		return std::unique_ptr<RendererAPI>(new RendererAPI());
	}

}