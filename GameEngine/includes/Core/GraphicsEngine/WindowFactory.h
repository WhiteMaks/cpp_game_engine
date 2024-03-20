#pragma once

#include "Core/GraphicsEngine/Window.h"

namespace GameEngine
{

	class WindowFactory
	{
	public:
		static Window* Create(const WindowData& windowData);
	};

}