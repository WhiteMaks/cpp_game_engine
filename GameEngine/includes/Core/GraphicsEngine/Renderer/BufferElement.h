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

		BufferElement(BufferElementType type, const std::string& name, bool normalized = false) noexcept;

		unsigned int GetCount() noexcept;
	};

}