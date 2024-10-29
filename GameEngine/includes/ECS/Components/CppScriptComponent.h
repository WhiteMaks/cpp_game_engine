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

		ScriptableEntity* (*InitScript)();
		void (*DestroyScript)(CppScriptComponent*);

		template<typename T>
		void Bind() noexcept
		{
			InitScript = [] ()
				{
					return static_cast<ScriptableEntity*>(new T());
				};

			DestroyScript = [] (CppScriptComponent* cppScriptComponent)
				{
					delete cppScriptComponent->instance;
					cppScriptComponent->instance = nullptr;
				};
		}
	};

}