#pragma once

#include "Core/Core.h"

//#include "Core/EventsSystem/KeyboardEventType.h"
//#include "Core/EventsSystem/KeyboardEvent.h"
//#include "Core/EventsSystem/Keyboard.h"

#include "Core/GraphicsEngine/Window.h"
#include "Core/GraphicsEngine/WindowFactory.h"

#include "Tools/Log.h"

namespace GameEngine
{

	class GAME_ENGINE_API Engine
	{
	private:
		std::unique_ptr<Window> window;

	public:
		Engine();
		
		virtual ~Engine();

	public:
		void Start();

	};

}