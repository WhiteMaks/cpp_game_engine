#include "Core/GraphicsEngine/Assets/TextureFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#include "Core/GraphicsEngine/GraphicsEngine.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLTexture.h"
#include "Core/GraphicsEngine/WebGL/WebGLTexture.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
#include "Core/GraphicsEngine/WebGL/WebGLTexture.h"
#endif

namespace GraphicsEngine
{

	Texture* TextureFactory::Create(const std::string& pathToTexture)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return new WebGLTexture(pathToTexture);
		case GraphicsAPI::OpenGL: return new OpenGLTexture(pathToTexture);
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return new WebGLTexture(pathToTexture);
#endif
		return new Texture(pathToTexture);
	}

}