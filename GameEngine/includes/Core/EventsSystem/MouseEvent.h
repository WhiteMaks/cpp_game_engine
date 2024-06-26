#pragma once

#include <queue>

#include "Core/Core.h"
#include "MouseEventType.h"

namespace EventsSystem
{

	class GAME_ENGINE_API MouseEvent
	{

	private:
		bool leftKeyIsPressed;
		bool rightKeyIsPressed;
		
		float positionX;
		float positionY;
		
		MouseEventType type;

	public:
		MouseEvent(
			const MouseEventType type, 
			const float positionX, const float positionY, 
			const bool leftKeyIsPressed, const bool rightKeyIsPressed
		) noexcept;

	public:
		bool LeftKeyIsPressed() const noexcept;
		bool RightKeyIsPressed() const noexcept;
		bool IsValid() const noexcept;

		float GetPositionX() const noexcept;
		float GetPositionY() const noexcept;

		void Invalidate() noexcept;

		std::pair<float, float> GetPositions() const noexcept;
	};

}