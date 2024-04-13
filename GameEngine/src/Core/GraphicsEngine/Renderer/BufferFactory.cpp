#include "Core/GraphicsEngine/Renderer/BufferFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#include "Core/GraphicsEngine/GraphicsEngine.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLVertexStaticBuffer.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLIndexStaticBuffer.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
#endif

namespace GraphicsEngine
{

	VertexStaticBuffer* BufferFactory::CreateVertexStaticBuffer(float* vertices, unsigned int size)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::OpenGL: return new OpenGLVertexStaticBuffer(vertices, size);
		default: throw;
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
#endif
	}

	IndexStaticBuffer* BufferFactory::CreateIndexStaticBuffer(unsigned int* indeces, unsigned int size)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::OpenGL: return new OpenGLIndexStaticBuffer(indeces, size);
		default: throw;
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
#endif
	}
}