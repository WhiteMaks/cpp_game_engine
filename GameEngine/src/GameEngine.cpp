#include "GameEngine.h"

namespace GameEngine
{

	Engine::Engine(const std::string& applicationTitle, const unsigned int applicationWidth, const unsigned int applicationHeight)
	{
		window = std::unique_ptr<Window>(
			WindowFactory::Create(
				WindowData(applicationTitle, applicationWidth, applicationHeight)
			)
		);

		eventManager = EventManager::GetInstance();
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

	void Engine::StartLoop()
	{
		GAME_ENGINE_INFO("Loop has started");
#ifdef GAME_ENGINE_PLATFORM_BROWSER
		emscripten_set_main_loop(Loop, 0, false);
#else
		while (!window->ShouldClose())
		{
			Loop();
		}
#endif
		GAME_ENGINE_INFO("Loop completed");
	}

	void Engine::Loop()
	{
		Input();
		Update();
		Render();
	}

	void Engine::Input()
	{
		Mouse* mouse = eventManager->GetMouse();
		if (!mouse->BufferIsEmpty())
		{
			const auto mouseEvent = mouse->Read();
			//GAME_ENGINE_TRACE("Mouse [{0},{1}]", mouseEvent->GetPositionX(), mouseEvent->GetPositionY());
		}

		Keyboard* keyboard = eventManager->GetKetboard();
		if (!keyboard->KeyBufferIsEmpty())
		{
			const auto keyboardEvent = keyboard->ReadKey();
			GAME_ENGINE_INFO("Keyboard [{0}]", (char)keyboardEvent->GetCode());
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
		GAME_ENGINE_INFO("Destruction completed");
#endif
	}

}