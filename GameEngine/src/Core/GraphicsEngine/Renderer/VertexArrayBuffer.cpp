#include "Core/GraphicsEngine/Renderer/VertexArrayBuffer.h"

namespace GraphicsEngine
{
	
	void VertexArrayBuffer::Init() noexcept
	{
	}

	void VertexArrayBuffer::Bind() noexcept
	{
	}

	void VertexArrayBuffer::Unbind() noexcept
	{
	}

	void VertexArrayBuffer::Destroy() noexcept
	{
	}

	void VertexArrayBuffer::AddVertexBuffer(std::shared_ptr<VertexStaticBuffer>& buffer) noexcept
	{
	}

	void VertexArrayBuffer::SetIndexBuffer(std::shared_ptr<IndexStaticBuffer>& buffer) noexcept
	{
	}

	std::vector<std::shared_ptr<VertexStaticBuffer>> VertexArrayBuffer::GetVertexStaticBuffers() noexcept
	{
		return vertexStaticBuffers;
	}

	std::shared_ptr<IndexStaticBuffer> VertexArrayBuffer::GetIndexStaticBuffer() noexcept
	{
		return indexStaticBuffer;
	}

}