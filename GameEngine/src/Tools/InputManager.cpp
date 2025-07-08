#include "Tools/InputManager.h"

#include "EventsSystem/EventManager.h"
#include "Tools/Time.h"

#include <glm/glm.hpp>

namespace GameEngine
{

	float InputManager::horizontalAxis = 0.0f;
	float InputManager::verticalAxis = 0.0f;
	float InputManager::axisSpeed = 5.0f;

	void InputManager::Update() noexcept
	{
		float targetHorizontal = 0.0f;
		float targetVertical = 0.0f;

		if (GetKeyboard()->KeyIsPressed(EventsSystem::EventManager::keyD))
		{
			targetHorizontal += 1.0f;
		}

		if (GetKeyboard()->KeyIsPressed(EventsSystem::EventManager::keyA))
		{
			targetHorizontal -= 1.0f;
		}
		
		if (GetKeyboard()->KeyIsPressed(EventsSystem::EventManager::keyW))
		{
			targetVertical += 1.0f;
		}
			
		if (GetKeyboard()->KeyIsPressed(EventsSystem::EventManager::keyS))
		{
			targetVertical -= 1.0f;
		}
		
		float deltaTime = Time::GetDeltaTime();

		horizontalAxis += (targetHorizontal - horizontalAxis) * axisSpeed * deltaTime;
		verticalAxis += (targetVertical - verticalAxis) * axisSpeed * deltaTime;

		horizontalAxis = glm::clamp(horizontalAxis, -1.0f, 1.0f);
		verticalAxis = glm::clamp(verticalAxis, -1.0f, 1.0f);
	}

	float InputManager::GetVerticalAxis() noexcept
	{
		return verticalAxis;
	}

	float InputManager::GetHorizontalAxis() noexcept
	{
		return horizontalAxis;
	}

	float InputManager::GetMouseXAxis() noexcept
	{
		return 0.0f;
	}

	float InputManager::GetMouseYAxis() noexcept
	{
		return 0.0f;
	}

	EventsSystem::Mouse* InputManager::GetMouse() noexcept
	{
		return EventsSystem::EventManager::GetInstance()->GetMouse();
	}

	EventsSystem::Keyboard* InputManager::GetKeyboard() noexcept
	{
		return EventsSystem::EventManager::GetInstance()->GetKeyboard();
	}
}