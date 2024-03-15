#include "Engine/Support/Log.h"

namespace GameEngine
{
	std::shared_ptr<spdlog::logger> Log::engineLogger;
	std::shared_ptr<spdlog::logger> Log::applicationLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		engineLogger = spdlog::stdout_color_mt("Engine");
		engineLogger->set_level(spdlog::level::trace);

		applicationLogger = spdlog::stdout_color_mt("Application");
		applicationLogger->set_level(spdlog::level::trace);
	}
}