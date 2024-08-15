#pragma once

#include <memory>

#include "RendererAPI.h"

namespace GraphicsEngine
{

	class RendererAPIFactory
	{
	public:
		static std::unique_ptr<RendererAPI> Create();
	};

}