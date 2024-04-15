#pragma once

#include "BufferElement.h"

namespace GraphicsEngine
{

	class BufferLayout
	{
	private:
		unsigned int stride;
		
		std::vector<BufferElement> elements;

	public:
		BufferLayout() noexcept;
		BufferLayout(std::vector<BufferElement> elements) noexcept;

	public:
		void Init() noexcept;
		void Destroy() noexcept;

		std::vector<BufferElement> GetElements() noexcept;

		unsigned int GetStride() noexcept;

	};	

}