#pragma once

#include "BufferLayout.h"

namespace GraphicsEngine
{

	class VertexStaticBuffer
	{
	protected:
		float* vertices;
		unsigned int size;

		BufferLayout layout;

	public:
		VertexStaticBuffer(float* vertices, unsigned int size) noexcept;

	public:
		virtual void Init() noexcept;
		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;
		virtual void Destroy() noexcept;

		virtual void SetLayout(const BufferLayout& layout) noexcept;
		virtual BufferLayout& GetLayout() noexcept;
	};

}