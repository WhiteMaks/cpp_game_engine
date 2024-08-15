#pragma once

#include "Core/GraphicsEngine/Window.h"

namespace GraphicsEngine
{

	class WindowFactory
	{
	public:
		static std::unique_ptr<Window> Create(const WindowData& windowData);
	};

}