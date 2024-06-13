#include "Tools/Log.h"

namespace GameEngine
{
	std::shared_ptr<spdlog::logger> Log::gameEngineLogger;
	std::shared_ptr<spdlog::logger> Log::graphicsEngineLogger;
	std::shared_ptr<spdlog::logger> Log::eventsSystemLogger;
	std::shared_ptr<spdlog::logger> Log::layerLogger;
	std::shared_ptr<spdlog::logger> Log::memoryLogger;
	std::shared_ptr<spdlog::logger> Log::applicationLogger;

	void Log::Init()
	{
		spdlog::set_pattern("[%T:%f] [%^%l%$] [%t] [%n] - %v");

		gameEngineLogger = spdlog::stdout_color_mt("Game engine");
		gameEngineLogger->set_level(spdlog::level::trace);

		graphicsEngineLogger = spdlog::stdout_color_mt("Graphics Engine");
		graphicsEngineLogger->set_level(spdlog::level::trace);

		eventsSystemLogger = spdlog::stdout_color_mt("Events system");
		eventsSystemLogger->set_level(spdlog::level::trace);

		layerLogger = spdlog::stdout_color_mt("Layer");
		layerLogger->set_level(spdlog::level::trace);

		memoryLogger = spdlog::stdout_color_mt("Memory");
		memoryLogger->set_level(spdlog::level::trace);

		applicationLogger = spdlog::stdout_color_mt("Application");
		applicationLogger->set_level(spdlog::level::trace);
	}
}