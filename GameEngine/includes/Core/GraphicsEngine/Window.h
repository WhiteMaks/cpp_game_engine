#pragma once

#include <string>

#include "Core/Core.h"

namespace GameEngine
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

	public:
		Window(const WindowData& windowData);

		virtual ~Window();

	public:
		virtual void Init();
		virtual void Update();
		virtual void Destroy();
		
		unsigned int GetWidth();
		unsigned int GetHeight();
	};

}