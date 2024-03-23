#include "Core/EventsSystem/EventManager.h"

namespace EventsSystem
{

	EventManager* EventManager::instance = nullptr;

	EventManager::EventManager() noexcept
	{
		mouse = new Mouse();
		keyboard = new Keyboard();
		window = new Window();
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

		EVENT_MANAGER_DEBUG("Initialization window has started");
		window->Flush();
		EVENT_MANAGER_DEBUG("Initialization window completed");

		EVENT_MANAGER_INFO("Initialization completed");
	}

	void EventManager::Destroy() noexcept
	{
		EVENT_MANAGER_INFO("Destruction has started");

		delete mouse;
		EVENT_MANAGER_TRACE("Mouse removed from memory");
		delete keyboard;
		EVENT_MANAGER_TRACE("Keyboard removed from memory");
		delete window;
		EVENT_MANAGER_TRACE("Window removed from memory");
		instance = nullptr;
		EVENT_MANAGER_TRACE("Instance is now null");

		EVENT_MANAGER_INFO("Destruction completed");
	}

	Mouse* EventManager::GetMouse() const noexcept
	{
		return mouse;
	}

	Keyboard* EventManager::GetKetboard() const noexcept
	{
		return keyboard;
	}

	Window* EventManager::GetWindow() const noexcept
	{
		return window;
	}

}