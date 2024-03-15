#pragma once

#include "Support/Core.h"
#include "Support/Log.h"

namespace GameEngine
{

	class GAME_ENGINE_API Engine
	{
	public:
		Engine();
		virtual ~Engine();

	public:
		void Start();

	};

}