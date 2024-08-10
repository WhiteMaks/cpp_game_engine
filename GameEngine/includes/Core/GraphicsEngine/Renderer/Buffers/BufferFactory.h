#pragma once

#include "Core/Core.h"
#include "IndexStaticBuffer.h"
#include "VertexStaticBuffer.h"
#include "VertexArrayBuffer.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API BufferFactory
	{
	public:
		static VertexStaticBuffer* CreateVertexStaticBuffer(float* vertices, unsigned int size);
		static IndexStaticBuffer* CreateIndexStaticBuffer(unsigned int* indeces, unsigned int size);
		static VertexArrayBuffer* CreateVertexArrayBuffer();

	};

}