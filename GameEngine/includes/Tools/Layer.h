#pragma once

#include <string>

#include "Core/Core.h"

#include "EventsSystem/MouseEvent.h"
#include "EventsSystem/KeyboardEvent.h"
#include "EventsSystem/WindowEvent.h"

namespace GameEngine
{

	class GAME_ENGINE_API Layer
	{

	protected:
		std::string name;

	public:
		Layer(const std::string& name) noexcept;
		virtual ~Layer() noexcept;

	public:
		virtual void Init() noexcept;
		virtual void Destroy() noexcept;
		virtual void Update() noexcept;
		virtual void Render() noexcept;
		virtual void MouseEvent(EventsSystem::MouseEvent& mouseEvent) noexcept;
		virtual void KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept;
		virtual void WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept;

		const std::string& GetName() const noexcept;

	};

}