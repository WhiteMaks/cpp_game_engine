#pragma once

#include <queue>
#include <bitset>
#include <optional>

#include "Core/Core.h"
#include "KeyboardEvent.h"

namespace EventsSystem
{

	class GAME_ENGINE_API Keyboard
	{

	private:
		static constexpr unsigned int nKeys = 256u;
		static constexpr unsigned int bufferSize = 16u;

		std::queue<KeyboardEvent> keyBuffer;
		std::queue<unsigned char> charBuffer;

		std::bitset<nKeys> keyStates;

	public:
		Keyboard() noexcept = default;

		Keyboard(const Keyboard&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;

	public:
		bool KeyBufferIsEmpty() const noexcept;
		bool KeyIsPressed(unsigned char keyCode) const noexcept;
		bool CharBufferIsEmpty() const noexcept;

		void FlushKeyBuffer() noexcept;
		void FlushCharBuffer() noexcept;
		void Flush() noexcept;

		void OnKeyPressed(unsigned char keyCode) noexcept;
		void OnKeyReleased(unsigned char keyCode) noexcept;
		void OnChar(unsigned char character) noexcept;

		std::optional<KeyboardEvent> ReadKey() noexcept;
		std::optional<unsigned char> ReadChar() noexcept;

	private:
		template<typename T>
		static void TrimBuffer(std::queue<T>& buffer) noexcept;
	};

}