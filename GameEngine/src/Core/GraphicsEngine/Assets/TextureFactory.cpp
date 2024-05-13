#include "Core/GraphicsEngine/Assets/TextureFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#include "Core/GraphicsEngine/GraphicsEngine.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
#endif

namespace GraphicsEngine
{

	Texture* TextureFactory::Create(const std::string& pathToTexture)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return nullptr;
		case GraphicsAPI::OpenGL: return nullptr;
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return nullptr;
#endif
		return new Texture();
	}

}