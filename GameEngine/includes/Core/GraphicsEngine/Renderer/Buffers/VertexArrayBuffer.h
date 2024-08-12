#pragma once

#include <memory>

#include "VertexStaticBuffer.h"
#include "IndexStaticBuffer.h"

namespace GraphicsEngine
{

	class VertexArrayBuffer
	{
	protected:
		std::vector<std::shared_ptr<VertexStaticBuffer>> vertexStaticBuffers;
		
		std::shared_ptr<IndexStaticBuffer> indexStaticBuffer;

	public:
		virtual void Init() noexcept;
		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;
		virtual void Destroy() noexcept;

		virtual void AddVertexBuffer(std::shared_ptr<VertexStaticBuffer>& buffer) noexcept;
		virtual void SetIndexBuffer(std::shared_ptr<IndexStaticBuffer>& buffer) noexcept;

		virtual std::vector<std::shared_ptr<VertexStaticBuffer>> GetVertexStaticBuffers() noexcept;
		virtual std::shared_ptr<IndexStaticBuffer> GetIndexStaticBuffer() noexcept;

	};

}