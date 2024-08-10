#include "Core/GraphicsEngine/Renderer/Buffers/VertexStaticBuffer.h"

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

	void VertexStaticBuffer::SetLayout(const BufferLayout& layout) noexcept
	{
		this->layout = layout;
	}

	BufferLayout& VertexStaticBuffer::GetLayout() noexcept
	{
		return layout;
	}

}