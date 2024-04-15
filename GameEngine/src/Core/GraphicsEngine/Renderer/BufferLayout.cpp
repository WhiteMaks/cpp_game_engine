#include "Core/GraphicsEngine/Renderer/BufferLayout.h"

namespace GraphicsEngine
{
	
	BufferLayout::BufferLayout() noexcept
	{
	}

	BufferLayout::BufferLayout(std::vector<BufferElement> elements) noexcept
		: elements(elements), stride(0)
	{
	}

	void BufferLayout::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization buffer layout has started");
		stride = 0;

		unsigned int offset = 0;
		for (auto& element : elements)
		{
			element.Offset = offset;
			
			offset += element.Size;
			stride += element.Size;
		}
		GRAPHICS_ENGINE_INFO("Initialization buffer layout completed");
	}

	void BufferLayout::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction buffer layout has started");

		GRAPHICS_ENGINE_INFO("Destruction buffer layout completed");
	}

	std::vector<BufferElement> BufferLayout::GetElements() noexcept
	{
		return elements;
	}

	unsigned int BufferLayout::GetStride() noexcept
	{
		return stride;
	}

}