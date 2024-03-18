#pragma once

#include "KeyboardEventType.h"

namespace GameEngine
{

	class KeyboardEvent
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