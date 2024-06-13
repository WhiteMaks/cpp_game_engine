#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "GameEngine.h"

namespace GameEngine
{
	Memory::TimedCache* GameEngine::timedCache = new Memory::TimedCache(2);

	GameEngine::GameEngine(const std::string& applicationTitle, const unsigned int applicationWidth, const unsigned int applicationHeight)
	{
		Log::Init();

		layerStack = new LayerStack();
#ifdef GAME_ENGINE_PLATFORM_BROWSER
		graphicsEngine = new GraphicsEngine::GraphicsEngine(applicationTitle, applicationWidth, applicationHeight, GraphicsEngine::GraphicsAPI::WebGL);
#else
		graphicsEngine = new GraphicsEngine::GraphicsEngine(applicationTitle, applicationWidth, applicationHeight, GraphicsEngine::GraphicsAPI::OpenGL);
#endif
		eventManager = EventsSystem::EventManager::GetInstance();
	}

	GameEngine::~GameEngine()
	{
	}

	Memory::TimedCache* GameEngine::GetTimedCache()
	{
		return timedCache;
	}

	void GameEngine::Start()
	{
		Init();
		StartLoop();
		Destroy();
	}

	void GameEngine::PushLayer(Layer* layer)
	{
		GAME_ENGINE_INFO("Saving of the new layer [{0}] has started", layer->GetName());
		layerStack->Push(layer);
		GAME_ENGINE_INFO("Saving of the new layer [{0}] completed", layer->GetName());
	}

	void GameEngine::PushOverlayLayer(Layer* layer)
	{
		GAME_ENGINE_INFO("Saving of the new layer [{0}] has started", layer->GetName());
		layerStack->PushOverlay(layer);
		GAME_ENGINE_INFO("Saving of the new layer [{0}] completed", layer->GetName());
	}

	void GameEngine::Init()
	{
		GAME_ENGINE_INFO("Initialization game engine has started");
		timedCache->Init();
		eventManager->Init();
		graphicsEngine->Init();
		layerStack->Init();

		Time::Init();
		GAME_ENGINE_INFO("Initialization game engine completed");
	}

#ifdef GAME_ENGINE_PLATFORM_BROWSER
	void RenderLoopCallback(void* arg)
	{
		static_cast<GameEngine*>(arg)->Loop();
	}
#endif

	void GameEngine::StartLoop()
	{
#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop_arg(&RenderLoopCallback, this, 0, false);
#else
		GAME_ENGINE_INFO("Loop has started");
		while (!graphicsEngine->ShouldStop())
		{
			Loop();
		}
		GAME_ENGINE_INFO("Loop completed");
#endif
	}

	void GameEngine::Loop()
	{
		Input();
		Update();
		Render();

		Time::Update();
	}

	void GameEngine::Input()
	{
		/*
		* If there is data in the event buffer, then read the event from the buffer and throw it into layers. 
		* If the event becomes invalid (due to processing of this event in a layer), then exit the loop (there is no point in throwing invalid event into layers).
		*/

		EventsSystem::Mouse* mouse = eventManager->GetMouse();
		if (!mouse->BufferIsEmpty())
		{
			EventsSystem::MouseEvent mouseEvent = mouse->Read().value();

			for (auto currentLayer = layerStack->end(); currentLayer != layerStack->begin(); )
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

			for (auto currentLayer = layerStack->end(); currentLayer != layerStack->begin(); )
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
				graphicsEngine->Stop();
				break;
			case EventsSystem::WindowEventType::RESIZE:
				break;
			}
		}
	}

	void GameEngine::Update()
	{
		graphicsEngine->BeginUpdate();

		for (Layer* layer : *layerStack)
		{
			layer->Update();
		}

		graphicsEngine->EndUpdate();
	}

	void GameEngine::Render()
	{
		graphicsEngine->BeginRender();

		for (Layer* layer : *layerStack)
		{
			layer->Render();
		}

		graphicsEngine->EndRender();
	}

	void GameEngine::Destroy()
	{
#ifdef GAME_ENGINE_PLATFORM_BROWSER
		
#else
		GAME_ENGINE_INFO("Destruction game engine has started");
		layerStack->Destroy();
		eventManager->Destroy();
		graphicsEngine->Destroy();
		timedCache->Destroy();
		GAME_ENGINE_INFO("Destruction game engine completed");
#endif
	}

}