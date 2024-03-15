#include "Engine/Engine.h"

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
		GAME_ENGINE_INFO("Engine initialization has started");

		GAME_ENGINE_INFO("Engine initialization completed");

		GAME_ENGINE_INFO("Engine loop has started");

		while (true);

		GAME_ENGINE_INFO("Engine loop completed");
	}

}