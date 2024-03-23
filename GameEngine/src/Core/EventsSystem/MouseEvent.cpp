#include "Core/EventsSystem/MouseEvent.h"

namespace GameEngine
{

	MouseEvent::MouseEvent(
		const MouseEventType type, 
		const float positionX, const float positionY, 
		const bool leftKeyIsPressed, const bool rightKeyIsPressed
	) noexcept
		: type(type), positionX(positionX), positionY(positionY), leftKeyIsPressed(leftKeyIsPressed), rightKeyIsPressed(rightKeyIsPressed)
	{

	}

	bool MouseEvent::LeftKeyIsPressed() const noexcept
	{
		return leftKeyIsPressed;
	}

	bool MouseEvent::RightKeyIsPressed() const noexcept
	{
		return rightKeyIsPressed;
	}

	bool MouseEvent::IsValid() const noexcept
	{
		return type != MouseEventType::NONE;
	}

	float MouseEvent::GetPositionX() const noexcept
	{
		return positionX;
	}

	float MouseEvent::GetPositionY() const noexcept
	{
		return positionY;
	}

	void MouseEvent::Invalidate() noexcept
	{
		type = MouseEventType::NONE;
	}

	std::pair<float, float> MouseEvent::GetPositions() const noexcept
	{
		return {positionX, positionY};
	}

}