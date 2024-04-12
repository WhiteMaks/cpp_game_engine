#pragma once

#include <SDL.h>

#include "Core/GraphicsEngine/Window.h"
#include "Tools/Log.h"

namespace Platform
{

	class BrowserWindow : public GraphicsEngine::Window
	{
	public:
		static SDL_Window* window;

	public:
		BrowserWindow(const GraphicsEngine::WindowData& windowData) noexcept;

	public:
		void Init() noexcept override;
		void Update() noexcept override;
		void Destroy() noexcept override;

	};

}