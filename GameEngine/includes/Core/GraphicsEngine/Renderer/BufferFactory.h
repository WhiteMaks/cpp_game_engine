#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace GraphicsEngine
{

	class BufferFactory
	{
	public:
		static VertexBuffer* CreateVertexBuffer(float* vertices, unsigned int size);
		static IndexBuffer* CreateIndexBuffer(unsigned int* indeces, unsigned int size);

	};

}