#pragma once

#include <memory>

#include "Core/Core.h"
#include "FrameBuffer.h"
#include "IndexStaticBuffer.h"
#include "VertexStaticBuffer.h"
#include "VertexDynamicBuffer.h"
#include "VertexArrayBuffer.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API BufferFactory
	{
	public:
		static std::shared_ptr<FrameBuffer> CreateFrameBuffer(const FrameBufferData& data);
		static std::shared_ptr<VertexStaticBuffer> CreateVertexStaticBuffer(float* vertices, unsigned int size);
		static std::shared_ptr<VertexDynamicBuffer> CreateVertexDynamicBuffer(unsigned int size);
		static std::shared_ptr<IndexStaticBuffer> CreateIndexStaticBuffer(unsigned int* indeces, unsigned int size);
		static std::shared_ptr<VertexArrayBuffer> CreateVertexArrayBuffer();

	};

}