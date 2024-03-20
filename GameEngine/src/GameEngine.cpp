#include "GameEngine.h"

namespace GameEngine
{

	Engine::Engine()
	{
		window = std::unique_ptr<Window>(WindowFactory::Create(WindowData("Window name", 1280, 720)));
	}

	Engine::~Engine()
	{

	}

	void Engine::Start()
	{
		GAME_ENGINE_INFO("Initialization has started");
		window->Init();
		GAME_ENGINE_INFO("Initialization completed");

		GAME_ENGINE_INFO("Loop has started");
		while (true)
		{
			window->Update();
		}
		GAME_ENGINE_INFO("Loop completed");

		GAME_ENGINE_INFO("Destruction has started");
		window->Destroy();
		GAME_ENGINE_INFO("Destruction completed");
	}

}