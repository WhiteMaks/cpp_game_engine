#pragma once

#include "Core/Core.h"

namespace GraphicsEngine
{

	struct GAME_ENGINE_API FrameBufferData
	{
		unsigned int Width;
		unsigned int Height;
		unsigned int Samples;

		bool SwapChainTarget;
	};

}