#include "Core/GraphicsEngine/Renderer/BufferFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#include "Core/GraphicsEngine/GraphicsEngine.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLVertexBuffer.h"
#include "Core/GraphicsEngine/OpenGL/OpenGLIndexBuffer.h"
#elif GAME_ENGINE_PLATFORM_BROWSER
#endif

namespace GraphicsEngine
{

	VertexBuffer* BufferFactory::CreateVertexBuffer(float* vertices, unsigned int size)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		default: throw;
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
#endif
	}

	IndexBuffer* BufferFactory::CreateIndexBuffer(unsigned int* indeces, unsigned int size)
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		switch (GraphicsEngine::GetAPI())
		{
		case GraphicsAPI::OpenGL: return new OpenGLIndexBuffer(indeces, size);
		default: throw;
		}
#elif GAME_ENGINE_PLATFORM_BROWSER
#endif
	}
}