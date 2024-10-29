#pragma once

#include "Entity.h"

namespace ECS
{

	class ScriptableEntity
	{

	private:
		Entity entity;
		friend class Scene;

	public:
		
		template<typename T>
		T& GetComponent()
		{
			return entity.GetComponent<T>();
		}

		virtual void Init() noexcept
		{
		}

		virtual void Update() noexcept
		{
		}

		virtual void Destroy() noexcept
		{
		}

		virtual void MouseEvent(EventsSystem::MouseEvent& mouseEvent) noexcept
		{
		}

		virtual void KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept
		{
		}

		virtual void WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept
		{
		}
	};

}