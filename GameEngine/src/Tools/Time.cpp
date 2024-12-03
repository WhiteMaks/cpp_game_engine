#include <chrono>

#include "Tools/Time.h"
#include "Tools/Log.h"

namespace GameEngine
{

	double Time::time = 0.0f;
	double Time::deltaTime = 0.0f;
	double Time::startTime = 0.0f;

	void Time::Init() noexcept
	{
		startTime = GetTime();
		time = startTime;
	}

	void Time::Update() noexcept
	{
		double temp = time;

		time = GetTime();

		deltaTime = (time - temp) / 1000000000.0;
	}

	double Time::GetSeconds() noexcept
	{
		return time / 1000000000.0;
	}

	double Time::GetMillieconds() noexcept
	{
		return time;
	}

	double Time::GetDeltaTime() noexcept
	{
		return deltaTime;
	}

	double Time::GetUptimeSeconds() noexcept
	{
		return GetSeconds() - (startTime / 1000000000.0);
	}

	double Time::GetTime() noexcept
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}
}