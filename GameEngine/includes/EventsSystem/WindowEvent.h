#pragma once

#include "Core/Core.h"
#include "WindowEventType.h"

namespace EventsSystem
{

	class GAME_ENGINE_API WindowEvent
	{

	private:
		unsigned int width;
		unsigned int height;

		WindowEventType type;

	public:
		WindowEvent(
			const WindowEventType type,
			const unsigned int width, const unsigned int height
		) noexcept;

	public:
		bool IsValid() const noexcept;

		unsigned int GetWidth() const noexcept;
		unsigned int GetHeight() const noexcept;

		WindowEventType GetType() const noexcept;

		void Invalidate() noexcept;

	};

}