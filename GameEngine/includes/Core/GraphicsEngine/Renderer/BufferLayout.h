#pragma once

#include "Core/Core.h"
#include "BufferElement.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API BufferLayout
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