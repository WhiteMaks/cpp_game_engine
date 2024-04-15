#include "Core/GraphicsEngine/Renderer/BufferElement.h"

namespace GraphicsEngine
{

	BufferElement::BufferElement(const std::string& name, BufferElementType type, bool normalized) noexcept
		: Name(name), Type(type), Size(GetBufferElementTypeSize(type)), Normalized(normalized), Offset(0)
	{
	}

	unsigned int BufferElement::GetCount() noexcept
	{
		switch (Type)
		{
		case GraphicsEngine::BufferElementType::FLOAT:		return 1;
		case GraphicsEngine::BufferElementType::FLOAT_2:	return 2;
		case GraphicsEngine::BufferElementType::FLOAT_3:	return 3;
		case GraphicsEngine::BufferElementType::FLOAT_4:	return 4;
		case GraphicsEngine::BufferElementType::INT:		return 1;
		case GraphicsEngine::BufferElementType::INT_2:		return 2;
		case GraphicsEngine::BufferElementType::INT_3:		return 3;
		case GraphicsEngine::BufferElementType::INT_4:		return 4;
		case GraphicsEngine::BufferElementType::BOOL:		return 1;
		case GraphicsEngine::BufferElementType::MAT_2:		return 2 * 2;
		case GraphicsEngine::BufferElementType::MAT_3:		return 3 * 3;
		case GraphicsEngine::BufferElementType::MAT_4:		return 4 * 4;
		}

		GAME_ENGINE_WARNING("Unexpected buffer element type, count will be equals 0!");

		return 0;
	}

}