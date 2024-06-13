#pragma once

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Core/Core.h"

namespace GameEngine
{

	class GAME_ENGINE_API Log
	{

	private:
		static std::shared_ptr<spdlog::logger> gameEngineLogger;
		static std::shared_ptr<spdlog::logger> graphicsEngineLogger;
		static std::shared_ptr<spdlog::logger> eventsSystemLogger;
		static std::shared_ptr<spdlog::logger> layerLogger;
		static std::shared_ptr<spdlog::logger> memoryLogger;
		static std::shared_ptr<spdlog::logger> applicationLogger;

	public:
		inline static std::shared_ptr<spdlog::logger>& GetGameEngineLogger()
		{
			return gameEngineLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetGraphicsEngineLogger()
		{
			return graphicsEngineLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetEventsSystemLogger()
		{
			return eventsSystemLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetLayerLogger()
		{
			return layerLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetMemoryLogger()
		{
			return memoryLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetApplicationLogger()
		{
			return applicationLogger;
		}

		static void Init();
	};

}

#define GAME_ENGINE_CRITICAL(...)	::GameEngine::Log::GetGameEngineLogger()->critical(__VA_ARGS__)
#define GAME_ENGINE_ERROR(...)		::GameEngine::Log::GetGameEngineLogger()->error(__VA_ARGS__)
#define GAME_ENGINE_WARNING(...)	::GameEngine::Log::GetGameEngineLogger()->warn(__VA_ARGS__)
#define GAME_ENGINE_INFO(...)		::GameEngine::Log::GetGameEngineLogger()->info(__VA_ARGS__)
#define GAME_ENGINE_DEBUG(...)		::GameEngine::Log::GetGameEngineLogger()->debug(__VA_ARGS__)
#define GAME_ENGINE_TRACE(...)		::GameEngine::Log::GetGameEngineLogger()->trace(__VA_ARGS__)

#define GRAPHICS_ENGINE_CRITICAL(...)		::GameEngine::Log::GetGraphicsEngineLogger()->critical(__VA_ARGS__)
#define GRAPHICS_ENGINE_ERROR(...)			::GameEngine::Log::GetGraphicsEngineLogger()->error(__VA_ARGS__)
#define GRAPHICS_ENGINE_WARNING(...)		::GameEngine::Log::GetGraphicsEngineLogger()->warn(__VA_ARGS__)
#define GRAPHICS_ENGINE_INFO(...)			::GameEngine::Log::GetGraphicsEngineLogger()->info(__VA_ARGS__)
#define GRAPHICS_ENGINE_DEBUG(...)			::GameEngine::Log::GetGraphicsEngineLogger()->debug(__VA_ARGS__)
#define GRAPHICS_ENGINE_TRACE(...)			::GameEngine::Log::GetGraphicsEngineLogger()->trace(__VA_ARGS__)

#define EVENTS_SYSTEM_CRITICAL(...)			::GameEngine::Log::GetEventsSystemLogger()->critical(__VA_ARGS__)
#define EVENTS_SYSTEM_ERROR(...)			::GameEngine::Log::GetEventsSystemLogger()->error(__VA_ARGS__)
#define EVENTS_SYSTEM_WARNING(...)			::GameEngine::Log::GetEventsSystemLogger()->warn(__VA_ARGS__)
#define EVENTS_SYSTEM_INFO(...)				::GameEngine::Log::GetEventsSystemLogger()->info(__VA_ARGS__)
#define EVENTS_SYSTEM_DEBUG(...)			::GameEngine::Log::GetEventsSystemLogger()->debug(__VA_ARGS__)
#define EVENTS_SYSTEM_TRACE(...)			::GameEngine::Log::GetEventsSystemLogger()->trace(__VA_ARGS__)

#define LAYER_CRITICAL(...)			::GameEngine::Log::GetLayerLogger()->critical(__VA_ARGS__)
#define LAYER_ERROR(...)			::GameEngine::Log::GetLayerLogger()->error(__VA_ARGS__)
#define LAYER_WARNING(...)			::GameEngine::Log::GetLayerLogger()->warn(__VA_ARGS__)
#define LAYER_INFO(...)				::GameEngine::Log::GetLayerLogger()->info(__VA_ARGS__)
#define LAYER_DEBUG(...)			::GameEngine::Log::GetLayerLogger()->debug(__VA_ARGS__)
#define LAYER_TRACE(...)			::GameEngine::Log::GetLayerLogger()->trace(__VA_ARGS__)

#define MEMORY_CRITICAL(...)		::GameEngine::Log::GetMemoryLogger()->critical(__VA_ARGS__)
#define MEMORY_ERROR(...)			::GameEngine::Log::GetMemoryLogger()->error(__VA_ARGS__)
#define MEMORY_WARNING(...)			::GameEngine::Log::GetMemoryLogger()->warn(__VA_ARGS__)
#define MEMORY_INFO(...)			::GameEngine::Log::GetMemoryLogger()->info(__VA_ARGS__)
#define MEMORY_DEBUG(...)			::GameEngine::Log::GetMemoryLogger()->debug(__VA_ARGS__)
#define MEMORY_TRACE(...)			::GameEngine::Log::GetMemoryLogger()->trace(__VA_ARGS__)

#define APPLICATION_CRITICAL(...)	::GameEngine::Log::GetApplicationLogger()->critical(__VA_ARGS__)
#define APPLICATION_ERROR(...)		::GameEngine::Log::GetApplicationLogger()->error(__VA_ARGS__)
#define APPLICATION_WARNING(...)	::GameEngine::Log::GetApplicationLogger()->warn(__VA_ARGS__)
#define APPLICATION_INFO(...)		::GameEngine::Log::GetApplicationLogger()->info(__VA_ARGS__)
#define APPLICATION_DEBUG(...)		::GameEngine::Log::GetApplicationLogger()->debug(__VA_ARGS__)
#define APPLICATION_TRACE(...)		::GameEngine::Log::GetApplicationLogger()->trace(__VA_ARGS__)