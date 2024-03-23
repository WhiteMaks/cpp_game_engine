#include "Core/EventsSystem/EventManager.h"

namespace GameEngine
{

	EventManager* EventManager::instance = nullptr;

	EventManager::EventManager() noexcept
	{
		mouse = new Mouse();
		keyboard = new Keyboard();
	}

	EventManager* EventManager::GetInstance() noexcept
	{
		if (instance == nullptr)
		{
			instance = new EventManager();
		}

		return instance;
	}

	void EventManager::Init() noexcept
	{
		EVENT_MANAGER_INFO("Initialization has started");
		
		EVENT_MANAGER_DEBUG("Initialization mouse has started");
		mouse->Flush();
		EVENT_MANAGER_DEBUG("Initialization mouse completed");

		EVENT_MANAGER_DEBUG("Initialization keyboard has started");
		keyboard->Flush();
		EVENT_MANAGER_DEBUG("Initialization keyboard completed");

		EVENT_MANAGER_INFO("Initialization completed");
	}

	Mouse* EventManager::GetMouse() const noexcept
	{
		return mouse;
	}

	Keyboard* EventManager::GetKetboard() const noexcept
	{
		return keyboard;
	}

}