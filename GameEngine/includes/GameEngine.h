#pragma once

#include <memory>

#include "Core/Core.h"

#include "Core/EventsSystem/EventManager.h"

#include "Core/GraphicsEngine/Window.h"
#include "Core/GraphicsEngine/WindowFactory.h"

#include "Tools/Log.h"

namespace GameEngine
{

	class GAME_ENGINE_API Engine
	{
	private:
		std::unique_ptr<GraphicsEngine::Window> window;
		
		EventsSystem::EventManager* eventManager;

	public:
		Engine(const std::string& applicationTitle, const unsigned int applicationWidth = 1280, const unsigned int applicationHeight = 720);
		
		virtual ~Engine();

	public:
		void Loop();
		void Start();

	private:
		void Init();
		void StartLoop();
		void Input();
		void Update();
		void Render();
		void Destroy();

	};

}