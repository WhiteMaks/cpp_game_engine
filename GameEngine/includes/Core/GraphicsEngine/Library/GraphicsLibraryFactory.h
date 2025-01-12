#pragma once

#include <memory>

#include "GraphicsLibrary.h"

namespace GraphicsEngine
{

	class GraphicsLibraryFactory
	{
	public:
		static std::shared_ptr<GraphicsLibrary> Create();
	};

}