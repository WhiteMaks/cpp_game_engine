#include "Core/GraphicsEngine/Renderer/IndexStaticBuffer.h"

namespace GraphicsEngine
{
	IndexStaticBuffer::IndexStaticBuffer(unsigned int* indeces, unsigned int count) noexcept
		: indeces(indeces), count(count)
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