#include "Core/EventsSystem/Keyboard.h"

namespace GameEngine
{

	bool Keyboard::KeyBufferIsEmpty() const noexcept
	{
		return keyBuffer.empty();
	}

	bool Keyboard::KeyIsPressed(unsigned char keyCode) const noexcept
	{
		return keyStates[keyCode];
	}

	bool Keyboard::CharBufferIsEmpty() const noexcept
	{
		return charBuffer.empty();
	}

	void Keyboard::FlushKeyBuffer() noexcept
	{
		keyBuffer = std::queue<KeyboardEvent>();
	}

	void Keyboard::FlushCharBuffer() noexcept
	{
		charBuffer = std::queue<unsigned char>();
	}

	void Keyboard::Flush() noexcept
	{
		FlushKeyBuffer();
		FlushCharBuffer();
	}

	void Keyboard::OnKeyPressed(unsigned char keyCode) noexcept
	{
		keyStates[keyCode] = true;
		keyBuffer.push(KeyboardEvent(KeyboardEventType::PRESS, keyCode));

		TrimBuffer(keyBuffer);
	}

	void Keyboard::OnKeyReleased(unsigned char keyCode) noexcept
	{
		keyStates[keyCode] = false;
		keyBuffer.push(KeyboardEvent(KeyboardEventType::RELEASE, keyCode));
		
		TrimBuffer(keyBuffer);
	}

	void Keyboard::OnChar(unsigned char character) noexcept
	{
		charBuffer.push(character);
		
		TrimBuffer(charBuffer);
	}

	std::optional<KeyboardEvent> Keyboard::ReadKey() noexcept
	{
		if (keyBuffer.size() > 0u)
		{
			KeyboardEvent keyboardEvent = keyBuffer.front();
			keyBuffer.pop();
			return keyboardEvent;
		}
		
		return {};
	}

	std::optional<unsigned char> Keyboard::ReadChar() noexcept
	{
		if (charBuffer.size() > 0u)
		{
			unsigned char charCode = charBuffer.front();
			charBuffer.pop();
			return charCode;
		}
		
		return {};
	}

	template<typename T>
	inline void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
	{
		while (buffer.size() > bufferSize)
		{
			buffer.pop();
		}
	}

}