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
		EVENTS_SYSTEM_INFO("Initialization event manager has started");
		
		EVENTS_SYSTEM_DEBUG("Initialization mouse has started");
		mouse->Flush();
		EVENTS_SYSTEM_DEBUG("Initialization mouse completed");

		EVENTS_SYSTEM_DEBUG("Initialization keyboard has started");
		keyboard->Flush();
		EVENTS_SYSTEM_DEBUG("Initialization keyboard completed");

		EVENTS_SYSTEM_DEBUG("Initialization window has started");
		window->Flush();
		EVENTS_SYSTEM_DEBUG("Initialization window completed");

		EVENTS_SYSTEM_INFO("Initialization event manager completed");
	}

	void EventManager::Destroy() noexcept
	{
		EVENTS_SYSTEM_INFO("Destruction event manager has started");

		delete mouse;
		EVENTS_SYSTEM_TRACE("Mouse removed from memory");
		delete keyboard;
		EVENTS_SYSTEM_TRACE("Keyboard removed from memory");
		delete window;
		EVENTS_SYSTEM_TRACE("Window removed from memory");
		instance = nullptr;
		EVENTS_SYSTEM_TRACE("Instance is now null");

		EVENTS_SYSTEM_INFO("Destruction event manager completed");
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