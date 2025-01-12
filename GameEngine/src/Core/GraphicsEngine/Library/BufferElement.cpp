#include "Core/GraphicsEngine/Library/BufferElement.h"

namespace GraphicsEngine
{

	BufferElement::BufferElement(BufferElementType type, const std::string& name, bool normalized) noexcept
		: Name(name), Type(type), Size(GetBufferElementTypeSize(type)), Normalized(normalized), Offset(0)
	{
	}

	unsigned int BufferElement::GetCount() noexcept
	{
		switch (Type)
		{
		case BufferElementType::FLOAT:		return 1;
		case BufferElementType::FLOAT_2:	return 2;
		case BufferElementType::FLOAT_3:	return 3;
		case BufferElementType::FLOAT_4:	return 4;
		case BufferElementType::INT:		return 1;
		case BufferElementType::INT_2:		return 2;
		case BufferElementType::INT_3:		return 3;
		case BufferElementType::INT_4:		return 4;
		case BufferElementType::BOOL:		return 1;
		case BufferElementType::MAT_2:		return 2 * 2;
		case BufferElementType::MAT_3:		return 3 * 3;
		case BufferElementType::MAT_4:		return 4 * 4;
		}

		GAME_ENGINE_WARNING("Unexpected buffer element type, count will be equals 0!");

		return 0;
	}

}