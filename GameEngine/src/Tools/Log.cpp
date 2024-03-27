#include "Tools/Log.h"

namespace GameEngine
{
	std::shared_ptr<spdlog::logger> Log::gameEngineLogger;
	std::shared_ptr<spdlog::logger> Log::windowLogger;
	std::shared_ptr<spdlog::logger> Log::eventManagerLogger;
	std::shared_ptr<spdlog::logger> Log::layerLogger;
	std::shared_ptr<spdlog::logger> Log::applicationLogger;

	void Log::Init()
	{
		spdlog::set_pattern("[%T:%f] [%^%l%$] [%t] [%n] - %v");

		gameEngineLogger = spdlog::stdout_color_mt("Game engine");
		gameEngineLogger->set_level(spdlog::level::trace);

		windowLogger = spdlog::stdout_color_mt("Window");
		windowLogger->set_level(spdlog::level::trace);

		eventManagerLogger = spdlog::stdout_color_mt("Event manager");
		eventManagerLogger->set_level(spdlog::level::trace);

		layerLogger = spdlog::stdout_color_mt("Layer");
		layerLogger->set_level(spdlog::level::trace);

		applicationLogger = spdlog::stdout_color_mt("Application");
		applicationLogger->set_level(spdlog::level::trace);
	}
}