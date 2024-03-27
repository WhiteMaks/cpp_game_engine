#pragma once

#include <string>

#include "Core/Core.h"
#include "Core/EventsSystem/MouseEvent.h"
#include "Core/EventsSystem/KeyboardEvent.h"

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
		virtual void Attach() noexcept;
		virtual void Detach() noexcept;
		virtual void Update() noexcept;
		virtual void Render() noexcept;
		virtual void MouseEvent(EventsSystem::MouseEvent& mouseEvent) noexcept;
		virtual void KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept;

		const std::string& GetName() const noexcept;

	};

}