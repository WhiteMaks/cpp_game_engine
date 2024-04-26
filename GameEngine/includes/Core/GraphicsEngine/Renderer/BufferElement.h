#pragma once

#include <string>

#include "Core/Core.h"
#include "BufferElementType.h"

namespace GraphicsEngine
{

	struct GAME_ENGINE_API BufferElement
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