#pragma once

#include "Core/Core.h"

#include "EventsSystem/Keyboard.h"
#include "EventsSystem/Mouse.h"

namespace GameEngine
{

	class GAME_ENGINE_API InputManager
	{

	private:
		static float horizontalAxis;
		static float verticalAxis;
		static float axisSpeed;

	public:
		static void Update() noexcept;

		static float GetVerticalAxis() noexcept;
		static float GetHorizontalAxis() noexcept;
		static float GetMouseXAxis() noexcept;
		static float GetMouseYAxis() noexcept;

		static EventsSystem::Mouse* GetMouse() noexcept;
		static EventsSystem::Keyboard* GetKeyboard() noexcept;
	};

}