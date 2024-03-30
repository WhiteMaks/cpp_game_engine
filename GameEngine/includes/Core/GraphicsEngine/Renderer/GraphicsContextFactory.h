#pragma once

#include "GraphicsContext.h"

namespace GraphicsEngine
{

	class GraphicsContextFactory
	{
	public:
		static GraphicsContext* Create();
	};

}