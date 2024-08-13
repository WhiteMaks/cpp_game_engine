#pragma once

#include "BufferLayout.h"

namespace GraphicsEngine
{

	class VertexDynamicBuffer
	{
	protected:
		float* vertices;
		unsigned int size;

		BufferLayout layout;

	public:
		VertexDynamicBuffer(unsigned int size) noexcept;

	public:
		virtual void Init() noexcept;
		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;
		virtual void Destroy() noexcept;

		virtual void SetLayout(const BufferLayout& layout) noexcept;
		virtual void SetData(const void* data, unsigned int size) noexcept;
		virtual BufferLayout& GetLayout() noexcept;
	};

}