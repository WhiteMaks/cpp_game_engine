#pragma once

#include "Core/GraphicsEngine/Window.h"

namespace GraphicsEngine
{

	class WindowFactory
	{
	public:
		static Window* Create(const WindowData& windowData);
	};

}