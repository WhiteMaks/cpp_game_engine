#pragma once

#include <string>

#include "Core/Core.h"
#include "Core/EventsSystem/EventManager.h"

namespace GraphicsEngine
{

	struct WindowData
	{
		std::string Title;

		unsigned int Width;
		unsigned int Height;

		WindowData(const std::string& title, unsigned int width, unsigned int height) noexcept;
	};

	class GAME_ENGINE_API Window
	{
	protected:
		WindowData windowData;

		bool shouldClose = true;

	public:
		Window(const WindowData& windowData) noexcept;

		virtual ~Window() noexcept;

	public:
		virtual void Init() noexcept;
		virtual void Update() noexcept;
		virtual void Destroy() noexcept;
		
		unsigned int GetWidth() const noexcept;
		unsigned int GetHeight() const noexcept;

		bool ShouldClose() const noexcept;
	};

}