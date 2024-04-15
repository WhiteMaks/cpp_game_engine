#pragma once

#include <string>

#include "BufferElementType.h"

namespace GraphicsEngine
{

	struct BufferElement
	{
		std::string Name;
		
		BufferElementType Type;

		unsigned int Offset;
		unsigned int Size;
		bool Normalized;

		BufferElement(const std::string& name, BufferElementType type, bool normalized = false) noexcept;

		unsigned int GetCount() noexcept;
	};

}