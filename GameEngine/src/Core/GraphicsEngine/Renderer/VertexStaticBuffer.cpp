#include "Core/GraphicsEngine/Renderer/VertexStaticBuffer.h"

namespace GraphicsEngine
{
	VertexStaticBuffer::VertexStaticBuffer(float* vertices, unsigned int size) noexcept
		: vertices(vertices), size(size)
	{
	}

	void VertexStaticBuffer::Init() noexcept
	{
	}

	void VertexStaticBuffer::Bind() noexcept
	{
	}

	void VertexStaticBuffer::Unbind() noexcept
	{
	}

	void VertexStaticBuffer::Destroy() noexcept
	{
	}

}