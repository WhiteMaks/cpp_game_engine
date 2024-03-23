#include "Core/EventsSystem/KeyboardEvent.h"

namespace EventsSystem
{

	KeyboardEvent::KeyboardEvent(const KeyboardEventType type, const unsigned char code) noexcept
		: type(type), code(code)
	{

	}

	bool KeyboardEvent::IsPressed() const noexcept
	{
		return type == KeyboardEventType::PRESS;
	}

	bool KeyboardEvent::IsReleased() const noexcept
	{
		return type == KeyboardEventType::RELEASE;
	}

	bool KeyboardEvent::IsValid() const noexcept
	{
		return type != KeyboardEventType::INVALID;
	}

	void KeyboardEvent::Invalidate() noexcept
	{
		type = KeyboardEventType::INVALID;
	}

	unsigned char KeyboardEvent::GetCode() const noexcept
	{
		return code;
	}

}