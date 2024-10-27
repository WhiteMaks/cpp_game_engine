#include "EventsSystem/WindowEvent.h"

namespace EventsSystem
{
	WindowEvent::WindowEvent(const WindowEventType type, const unsigned int width, const unsigned int height) noexcept
		: type(type), width(width), height(height)
	{
	}

	bool WindowEvent::IsValid() const noexcept
	{
		return type != WindowEventType::INVALID;
	}

	unsigned int WindowEvent::GetWidth() const noexcept
	{
		return width;
	}

	unsigned int WindowEvent::GetHeight() const noexcept
	{
		return height;
	}

	WindowEventType WindowEvent::GetType() const noexcept
	{
		return type;
	}

	void WindowEvent::Invalidate() noexcept
	{
		type = WindowEventType::INVALID;
	}

}