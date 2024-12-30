#pragma once

#include "Core/Core.h"

namespace GameEngine
{

	class GAME_ENGINE_API Time
	{
	private:
		double static time;
		double static deltaTime;
		double static startTime;

	public:
		static void Init() noexcept;
		static void Update() noexcept;

		static double GetSeconds() noexcept;
		static double GetMillieconds() noexcept;
		static double GetDeltaTime() noexcept;

		static double GetUptimeSeconds() noexcept;

	private:
		static double GetTime() noexcept;
	};

}