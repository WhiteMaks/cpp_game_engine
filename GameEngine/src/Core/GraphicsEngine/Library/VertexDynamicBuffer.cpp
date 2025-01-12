#include "Core/GraphicsEngine/Library/VertexDynamicBuffer.h"

namespace GraphicsEngine
{

	VertexDynamicBuffer::VertexDynamicBuffer(unsigned int size) noexcept
		: size(size), vertices(nullptr)
	{
	}

	void VertexDynamicBuffer::Init() noexcept
	{
	}

	void VertexDynamicBuffer::Bind() noexcept
	{
	}

	void VertexDynamicBuffer::Unbind() noexcept
	{
	}

	void VertexDynamicBuffer::Destroy() noexcept
	{
	}

	void VertexDynamicBuffer::SetLayout(const BufferLayout& layout) noexcept
	{
		this->layout = layout;
	}

	void VertexDynamicBuffer::SetData(const void* data, unsigned int size) noexcept
	{
	}

	BufferLayout& VertexDynamicBuffer::GetLayout() noexcept
	{
		return layout;
	}

}