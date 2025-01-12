#include "Core/GraphicsEngine/Library/IndexStaticBuffer.h"

namespace GraphicsEngine
{

	IndexStaticBuffer::IndexStaticBuffer(unsigned int* indices, unsigned int count) noexcept
		: indices(indices), count(count)
	{
	}

	void IndexStaticBuffer::Init() noexcept
	{
	}

	void IndexStaticBuffer::Bind() noexcept
	{
	}

	void IndexStaticBuffer::Unbind() noexcept
	{
	}

	void IndexStaticBuffer::Destroy() noexcept
	{
	}

	unsigned int IndexStaticBuffer::GetCount() noexcept
	{
		return count;
	}

}