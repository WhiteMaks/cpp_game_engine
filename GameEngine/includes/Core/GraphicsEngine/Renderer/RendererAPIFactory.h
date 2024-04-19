#pragma once

#include "RendererAPI.h"

namespace GraphicsEngine
{

	class RendererAPIFactory
	{
	public:
		static RendererAPI* Create();
	};

}