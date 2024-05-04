#include "Core/EventsSystem/EventManager.h"

namespace EventsSystem
{

	EventManager* EventManager::instance = nullptr;

	int EventManager::keyA = -1;
	int EventManager::keyB = -1;
	int EventManager::keyC = -1;
	int EventManager::keyD = -1;
	int EventManager::keyE = -1;
	int EventManager::keyF = -1;
	int EventManager::keyG = -1;
	int EventManager::keyH = -1;
	int EventManager::keyI = -1;
	int EventManager::keyJ = -1;
	int EventManager::keyK = -1;
	int EventManager::keyL = -1;
	int EventManager::keyM = -1;
	int EventManager::keyN = -1;
	int EventManager::keyO = -1;
	int EventManager::keyP = -1;
	int EventManager::keyQ = -1;
	int EventManager::keyR = -1;
	int EventManager::keyS = -1;
	int EventManager::keyT = -1;
	int EventManager::keyU = -1;
	int EventManager::keyV = -1;
	int EventManager::keyW = -1;
	int EventManager::keyX = -1;
	int EventManager::keyY = -1;
	int EventManager::keyZ = -1;

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