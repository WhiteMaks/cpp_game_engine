#pragma once

#include <SDL.h>

#include "Core/GraphicsEngine/Window.h"
#include "Tools/Log.h"

namespace Platform
{

	class BrowserWindow : public GraphicsEngine::Window
	{
	private:
		SDL_Window* window;

	public:
		BrowserWindow(const GraphicsEngine::WindowData& windowData) noexcept;

		virtual ~BrowserWindow() noexcept;

	public:
		void Init() noexcept override;
		void Update() noexcept override;
		void Destroy() noexcept override;

	};

}