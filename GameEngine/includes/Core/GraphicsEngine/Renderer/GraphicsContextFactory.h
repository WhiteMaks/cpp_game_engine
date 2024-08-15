#pragma once

#include <memory>

#include "GraphicsContext.h"

namespace GraphicsEngine
{

	class GraphicsContextFactory
	{
	public:
		static std::unique_ptr<GraphicsContext> Create();
	};

}