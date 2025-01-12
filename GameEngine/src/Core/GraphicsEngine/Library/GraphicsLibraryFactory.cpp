#include "Core/GraphicsEngine/Library/GraphicsLibraryFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#include "Core/GraphicsEngine/GraphicsEngine.h"
#include "Core/GraphicsEngine/Library/OpenGL/OpenGLGraphicsLibrary.h"
#include "Core/GraphicsEngine/Library/WebGL/WebGLGraphicsLibrary.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
#include "Core/GraphicsEngine/Library/WebGL/WebGLGraphicsLibrary.h"
#endif

namespace GraphicsEngine
{

	std::shared_ptr<GraphicsLibrary> GraphicsLibraryFactory::Create()
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
			case GraphicsAPI::WebGL: return std::shared_ptr<GraphicsLibrary>(new WebGLGraphicsLibrary());
			case GraphicsAPI::OpenGL: return std::shared_ptr<GraphicsLibrary>(new OpenGLGraphicsLibrary());
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return std::shared_ptr<GraphicsLibrary>(new WebGLGraphicsLibrary());
#endif
		return std::shared_ptr<GraphicsLibrary>(new GraphicsLibrary());
	}

}