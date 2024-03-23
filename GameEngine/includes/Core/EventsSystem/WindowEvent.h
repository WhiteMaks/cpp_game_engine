#pragma once

#include "WindowEventType.h"

namespace EventsSystem
{

	class WindowEvent
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