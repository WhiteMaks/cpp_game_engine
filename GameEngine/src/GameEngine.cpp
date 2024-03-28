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

	void Engine::PushLayer(Layer* layer)
	{
		GAME_ENGINE_INFO("Saving of the new layer [{0}] has started", layer->GetName());
		layerStack.Push(layer);
		GAME_ENGINE_INFO("Saving of the new layer [{0}] completed", layer->GetName());
	}

	void Engine::PushOverlayLayer(Layer* layer)
	{
		GAME_ENGINE_INFO("Saving of the new layer [{0}] has started", layer->GetName());
		layerStack.PushOverlay(layer);
		GAME_ENGINE_INFO("Saving of the new layer [{0}] completed", layer->GetName());
	}

	void Engine::Init()
	{
		GAME_ENGINE_INFO("Initialization has started");
		layerStack.Init();
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
		Input();
		Update();
		Render();
	}

	void Engine::Input()
	{
		/*
		* If there is data in the event buffer, then read the event from the buffer and throw it into layers. 
		* If the event becomes invalid (due to processing of this event in a layer), then exit the loop (there is no point in throwing invalid event into layers).
		*/

		EventsSystem::Mouse* mouse = eventManager->GetMouse();
		if (!mouse->BufferIsEmpty())
		{
			EventsSystem::MouseEvent mouseEvent = mouse->Read().value();

			for (auto currentLayer = layerStack.end(); currentLayer != layerStack.begin(); )
			{
				(*--currentLayer)->MouseEvent(mouseEvent);
				
				if (!mouseEvent.IsValid())
				{
					break;
				}
			}
		}

		EventsSystem::Keyboard* keyboard = eventManager->GetKetboard();
		if (!keyboard->KeyBufferIsEmpty())
		{
			EventsSystem::KeyboardEvent keyboardEvent = keyboard->ReadKey().value();

			for (auto currentLayer = layerStack.end(); currentLayer != layerStack.begin(); )
			{
				(*--currentLayer)->KeyboardEvent(keyboardEvent);

				if (!keyboardEvent.IsValid())
				{
					break;
				}
			}
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
		for (Layer* layer : layerStack)
		{
			layer->Update();
		}
		window->Update();
	}

	void Engine::Render()
	{
		for (Layer* layer : layerStack)
		{
			layer->Render();
		}
	}

	void Engine::Destroy()
	{
#ifdef GAME_ENGINE_PLATFORM_BROWSER
		
#else
		GAME_ENGINE_INFO("Destruction has started");
		window->Destroy();
		eventManager->Destroy();
		layerStack.Destroy();
		GAME_ENGINE_INFO("Destruction completed");
#endif
	}

}