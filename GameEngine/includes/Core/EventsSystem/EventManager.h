#pragma once

#include <memory>

#include "Keyboard.h"
#include "Mouse.h"
#include "Tools/Log.h"

namespace GameEngine
{

	class EventManager
	{
	private:
		static EventManager* instance;

		Mouse* mouse;
		Keyboard* keyboard;

	public:
		~EventManager() = delete;

		EventManager(EventManager& other) = delete;

		void operator=(const EventManager& ev) = delete;

	private:
		EventManager() noexcept;

	public:
		static EventManager* GetInstance() noexcept;

		void Init() noexcept;

		Mouse* GetMouse() const noexcept;
		Keyboard* GetKetboard() const noexcept;

	};

}