#pragma once

#include "Component.h"
#include "Core/Core.h"
#include "ECS/ScriptableEntity.h"
#include "ECS/Entity.h"
#include "EventsSystem/KeyboardEvent.h"
#include "EventsSystem/MouseEvent.h"
#include "EventsSystem/WindowEvent.h"

namespace ECS
{

	struct GAME_ENGINE_API CppScriptComponent : public Component
	{
		ScriptableEntity* instance = nullptr;

		std::function<void()> InitFunction;
		std::function<void()> DestroyFunction;

		std::function<void(ScriptableEntity*)> InitScriptFunction;
		std::function<void(ScriptableEntity*)> UpdateScriptFunction;
		std::function<void(ScriptableEntity*)> DestroyScriptFunction;
		std::function<void(ScriptableEntity*, EventsSystem::MouseEvent&)> MouseEventScriptFunction;
		std::function<void(ScriptableEntity*, EventsSystem::KeyboardEvent&)> KeyboardEventScriptFunction;
		std::function<void(ScriptableEntity*, EventsSystem::WindowEvent&)> WindowEventScriptFunction;

		template<typename T>
		void Bind() noexcept
		{
			InitFunction = [&] ()
				{
					instance = new T();
				};

			DestroyFunction = [&] ()
				{
					delete (T*) instance;
					instance = nullptr;
				};

			InitScriptFunction = [] (ScriptableEntity* instance)
				{
					((T*) instance)->Init();
				};

			UpdateScriptFunction = [] (ScriptableEntity* instance)
				{
					((T*) instance)->Update();
				};

			DestroyScriptFunction = [] (ScriptableEntity* instance)
				{
					((T*) instance)->Destroy();
				};

			MouseEventScriptFunction = [] (ScriptableEntity* instance, EventsSystem::MouseEvent& mouseEvent)
				{
					((T*) instance)->MouseEvent(mouseEvent);
				};

			KeyboardEventScriptFunction = [] (ScriptableEntity* instance, EventsSystem::KeyboardEvent& keyboardEvent)
				{
					((T*) instance)->KeyboardEvent(keyboardEvent);
				};

			WindowEventScriptFunction = [] (ScriptableEntity* instance, EventsSystem::WindowEvent& windowEvent)
				{
					((T*) instance)->WindowEvent(windowEvent);
				};
		}
	};

}