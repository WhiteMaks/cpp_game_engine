#include "GameEngine.h"

namespace GameEngine
{

	Engine::Engine()
	{

	}

	Engine::~Engine()
	{

	}

	void Engine::Start()
	{
		GAME_ENGINE_INFO("Initialization has started");

		GAME_ENGINE_INFO("Initialization completed");

		GAME_ENGINE_INFO("Loop has started");
		while (true);
		GAME_ENGINE_INFO("Loop completed");
	}

}