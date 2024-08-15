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
	std::shared_ptr<Texture> TextureFactory::Create(const unsigned int width, const unsigned int height)
	{
		#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return std::shared_ptr<Texture>(new WebGLTexture(width, height));
		case GraphicsAPI::OpenGL: return std::shared_ptr<Texture>(new OpenGLTexture(width, height));
		}
		#elif GAME_ENGINE_PLATFORM_BROWSER
		return std::shared_ptr<Texture>(new WebGLTexture(width, height));
		#endif
		return std::shared_ptr<Texture>(new Texture(width, height));
	}

	std::shared_ptr<Texture> TextureFactory::Create(const std::string& pathToTexture)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::WebGL: return std::shared_ptr<Texture>(new WebGLTexture(pathToTexture));
		case GraphicsAPI::OpenGL: return std::shared_ptr<Texture>(new OpenGLTexture(pathToTexture));
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
		return std::shared_ptr<Texture>(new WebGLTexture(pathToTexture));
#endif
		return std::shared_ptr<Texture>(new Texture(pathToTexture));
	}

}