#pragma once

#include "Core/Core.h"

#include "BufferLayout.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API VertexStaticBuffer
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