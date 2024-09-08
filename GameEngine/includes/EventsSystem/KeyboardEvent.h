#pragma once

#include "Core/Core.h"
#include "KeyboardEventType.h"

namespace EventsSystem
{

	class GAME_ENGINE_API KeyboardEvent
	{

	private:
		unsigned char code;

		KeyboardEventType type;

	public:
		KeyboardEvent(const KeyboardEventType type, const unsigned char code) noexcept;

	public:
		bool IsPressed() const noexcept;
		bool IsReleased() const noexcept;
		bool IsValid() const noexcept;

		void Invalidate() noexcept;

		unsigned char GetCode() const noexcept;
	};

}