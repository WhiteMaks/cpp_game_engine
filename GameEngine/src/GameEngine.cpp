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