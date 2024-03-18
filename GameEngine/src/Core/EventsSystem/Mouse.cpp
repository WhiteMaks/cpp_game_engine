#include "Core/EventsSystem/Mouse.h"

namespace GameEngine
{
	bool Mouse::LeftKeyIsPressed() const noexcept
	{
		return leftKeyIsPressed;
	}

	bool Mouse::RightKeyIsPressed() const noexcept
	{
		return rightKeyIsPressed;
	}

	bool Mouse::BufferIsEmpty() const noexcept
	{
		return buffer.empty();
	}

	void Mouse::Flush() noexcept
	{
		buffer = std::queue<MouseEvent>();
	}

	void Mouse::OnMouseMove(float positionX, float positionY) noexcept
	{
		this->positionX = positionX;
		this->positionY = positionY;

		buffer.push(MouseEvent(MouseEventType::MOVE, this->positionX, this->positionY, this->leftKeyIsPressed, this->rightKeyIsPressed));
		TrimBuffer(buffer);
	}

	void Mouse::OnLeftKeyPressed(float positionX, float positionY) noexcept
	{
		leftKeyIsPressed = true;

		this->positionX = positionX;
		this->positionY = positionY;

		buffer.push(MouseEvent(MouseEventType::L_PRESS, this->positionX, this->positionY, this->leftKeyIsPressed, this->rightKeyIsPressed));
		TrimBuffer(buffer);
	}

	void Mouse::OnLeftKeyReleased(float positionX, float positionY) noexcept
	{
		leftKeyIsPressed = false;

		this->positionX = positionX;
		this->positionY = positionY;

		buffer.push(MouseEvent(MouseEventType::L_RELEASE, this->positionX, this->positionY, this->leftKeyIsPressed, this->rightKeyIsPressed));
		TrimBuffer(buffer);
	}

	void Mouse::OnRightKeyPressed(float positionX, float positionY) noexcept
	{
		rightKeyIsPressed = true;

		this->positionX = positionX;
		this->positionY = positionY;

		buffer.push(MouseEvent(MouseEventType::R_PRESS, this->positionX, this->positionY, this->leftKeyIsPressed, this->rightKeyIsPressed));
		TrimBuffer(buffer);
	}

	void Mouse::OnRightKeyReleased(float positionX, float positionY) noexcept
	{
		rightKeyIsPressed = false;

		this->positionX = positionX;
		this->positionY = positionY;

		buffer.push(MouseEvent(MouseEventType::R_RELEASE, this->positionX, this->positionY, this->leftKeyIsPressed, this->rightKeyIsPressed));
		TrimBuffer(buffer);
	}

	std::optional<MouseEvent> Mouse::Read() noexcept
	{
		if (buffer.size() > 0u)
		{
			MouseEvent mouseEvent = buffer.front();
			buffer.pop();
			return mouseEvent;
		}

		return {};
	}

	template<typename T>
	inline void Mouse::TrimBuffer(std::queue<T>& buffer) noexcept
	{
		while (buffer.size() > bufferSize)
		{
			buffer.pop();
		}
	}
}