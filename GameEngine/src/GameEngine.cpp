#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "GameEngine.h"

namespace GameEngine
{

	Engine::Engine(const std::string& applicationTitle, const unsigned int applicationWidth, const unsigned int applicationHeight)
	{
		window = std::unique_ptr<GraphicsEngine::Window>(
			GraphicsEngine::WindowFactory::Create(
				GraphicsEngine::WindowData(applicationTitle, applicationWidth, applicationHeight)
			)
		);

		eventManager = EventsSystem::EventManager::GetInstance();
	}

	Engine::~Engine()
	{
	}

	void Engine::Start()
	{
		Init();
		StartLoop();
		Destroy();
	}

	void Engine::Init()
	{
		GAME_ENGINE_INFO("Initialization has started");
		eventManager->Init();
		window->Init();
		GAME_ENGINE_INFO("Initialization completed");
	}

#ifdef GAME_ENGINE_PLATFORM_BROWSER
	void RenderLoopCallback(void* arg)
	{
		static_cast<Engine*>(arg)->Loop();
	}
#endif

	void Engine::StartLoop()
	{
#ifdef GAME_ENGINE_PLATFORM_BROWSER
		emscripten_set_main_loop_arg(&RenderLoopCallback, this, 0, false);
#else
		GAME_ENGINE_INFO("Loop has started");
		while (!window->ShouldClose())
		{
			Loop();
		}
		GAME_ENGINE_INFO("Loop completed");
#endif
	}

	void Engine::Loop()
	{
		GAME_ENGINE_TRACE("Looping");
		Input();
		Update();
		Render();
	}

	void Engine::Input()
	{
		EventsSystem::Mouse* mouse = eventManager->GetMouse();
		if (!mouse->BufferIsEmpty())
		{
			const auto mouseEvent = mouse->Read();
		}

		EventsSystem::Keyboard* keyboard = eventManager->GetKetboard();
		if (!keyboard->KeyBufferIsEmpty())
		{
			const auto keyboardEvent = keyboard->ReadKey();
		}

		EventsSystem::Window* window = eventManager->GetWindow();
		if (!window->BufferIsEmpty())
		{
			const auto windowEvent = window->Read();

			EventsSystem::WindowEventType eventType = windowEvent->GetType();
			
			switch (eventType)
			{
			case EventsSystem::WindowEventType::CLOSE:
				this->window->ShouldClose(true);
				break;
			case EventsSystem::WindowEventType::RESIZE:
				break;
			}
		}
	}

	void Engine::Update()
	{
		window->Update();
	}

	void Engine::Render()
	{
	}

	void Engine::Destroy()
	{
#ifdef GAME_ENGINE_PLATFORM_BROWSER
		
#else
		GAME_ENGINE_INFO("Destruction has started");
		window->Destroy();
		eventManager->Destroy();
		GAME_ENGINE_INFO("Destruction completed");
#endif
	}

}