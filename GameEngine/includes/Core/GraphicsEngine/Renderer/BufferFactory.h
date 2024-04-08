#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace GraphicsEngine
{

	class BufferFactory
	{
	public:
		static VertexBuffer* CreateVertexBuffer();
		static IndexBuffer* CreateIndexBuffer();

	};

}