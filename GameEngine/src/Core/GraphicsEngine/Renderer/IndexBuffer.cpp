#include "Core/GraphicsEngine/Renderer/IndexBuffer.h"

namespace GraphicsEngine
{
	IndexBuffer::IndexBuffer(unsigned int* indeces, unsigned int count) noexcept
		: indeces(indeces), count(count)
	{
	}

	void IndexBuffer::Init() noexcept
	{
	}

	void IndexBuffer::Bind() noexcept
	{
	}

	void IndexBuffer::Unbind() noexcept
	{
	}

	void IndexBuffer::Destroy() noexcept
	{
	}

	unsigned int IndexBuffer::GetCount() noexcept
	{
		return count;
	}

}