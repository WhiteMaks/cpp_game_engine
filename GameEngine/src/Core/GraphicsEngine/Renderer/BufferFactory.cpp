#include "Core/GraphicsEngine/Renderer/BufferFactory.h"

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
#elif GAME_ENGINE_PLATFORM_BROWSER
#endif

namespace GraphicsEngine
{

	VertexBuffer* BufferFactory::CreateVertexBuffer(float* vertices, unsigned int size)
	{
		return nullptr;
	}

	IndexBuffer* BufferFactory::CreateIndexBuffer(unsigned int* indeces, unsigned int size)
	{
		return nullptr;
	}
}