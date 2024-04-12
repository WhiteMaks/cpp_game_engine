#pragma once

#include <Windows.h>

#include "Core/GraphicsEngine/Window.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace Platform
{

	class WindowsWindow : public GraphicsEngine::Window
	{
	private:
		HINSTANCE hInstance;

	public:
		static HWND window;

	public:
		WindowsWindow(const GraphicsEngine::WindowData& windowData) noexcept;

	public:
		void Init() noexcept override;
		void Update() noexcept override;
		void Destroy() noexcept override;

	};

}