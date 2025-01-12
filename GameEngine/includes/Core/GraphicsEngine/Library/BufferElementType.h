#pragma once

#include "Tools/Log.h"

namespace GraphicsEngine
{

	enum class BufferElementType
	{
		FLOAT,
		FLOAT_2,
		FLOAT_3,
		FLOAT_4,
		INT,
		INT_2,
		INT_3,
		INT_4,
		BOOL,
		MAT_2,
		MAT_3,
		MAT_4,
	};

	static unsigned int GetBufferElementTypeSize(BufferElementType type)
	{
		switch (type)
		{
		case BufferElementType::FLOAT:		return 4;
		case BufferElementType::FLOAT_2:	return 4 * 2;
		case BufferElementType::FLOAT_3:	return 4 * 3;
		case BufferElementType::FLOAT_4:	return 4 * 4;
		case BufferElementType::INT:		return 4;
		case BufferElementType::INT_2:		return 4 * 2;
		case BufferElementType::INT_3:		return 4 * 3;
		case BufferElementType::INT_4:		return 4 * 4;
		case BufferElementType::BOOL:		return 1;
		case BufferElementType::MAT_2:		return 4 * 2 * 2;
		case BufferElementType::MAT_3:		return 4 * 3 * 3;
		case BufferElementType::MAT_4:		return 4 * 4 * 4;
		}

		GAME_ENGINE_WARNING("Unexpected buffer element type, size will be equals 0!");

		return 0;
	}

}