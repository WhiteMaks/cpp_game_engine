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
		static std::shared_ptr<spdlog::logger> windowLogger;
		static std::shared_ptr<spdlog::logger> eventManagerLogger;
		static std::shared_ptr<spdlog::logger> applicationLogger;

	public:
		inline static std::shared_ptr<spdlog::logger>& GetGameEngineLogger()
		{
			return gameEngineLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetWindowLogger()
		{
			return windowLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetEventManagerLogger()
		{
			return eventManagerLogger;
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

#define WINDOW_CRITICAL(...)		::GameEngine::Log::GetWindowLogger()->critical(__VA_ARGS__)
#define WINDOW_ERROR(...)			::GameEngine::Log::GetWindowLogger()->error(__VA_ARGS__)
#define WINDOW_WARNING(...)			::GameEngine::Log::GetWindowLogger()->warn(__VA_ARGS__)
#define WINDOW_INFO(...)			::GameEngine::Log::GetWindowLogger()->info(__VA_ARGS__)
#define WINDOW_DEBUG(...)			::GameEngine::Log::GetWindowLogger()->debug(__VA_ARGS__)
#define WINDOW_TRACE(...)			::GameEngine::Log::GetWindowLogger()->trace(__VA_ARGS__)

#define EVENT_MANAGER_CRITICAL(...)	::GameEngine::Log::GetEventManagerLogger()->critical(__VA_ARGS__)
#define EVENT_MANAGER_ERROR(...)	::GameEngine::Log::GetEventManagerLogger()->error(__VA_ARGS__)
#define EVENT_MANAGER_WARNING(...)	::GameEngine::Log::GetEventManagerLogger()->warn(__VA_ARGS__)
#define EVENT_MANAGER_INFO(...)		::GameEngine::Log::GetEventManagerLogger()->info(__VA_ARGS__)
#define EVENT_MANAGER_DEBUG(...)	::GameEngine::Log::GetEventManagerLogger()->debug(__VA_ARGS__)
#define EVENT_MANAGER_TRACE(...)	::GameEngine::Log::GetEventManagerLogger()->trace(__VA_ARGS__)

#define APPLICATION_CRITICAL(...)	::GameEngine::Log::GetApplicationLogger()->critical(__VA_ARGS__)
#define APPLICATION_ERROR(...)		::GameEngine::Log::GetApplicationLogger()->error(__VA_ARGS__)
#define APPLICATION_WARNING(...)	::GameEngine::Log::GetApplicationLogger()->warn(__VA_ARGS__)
#define APPLICATION_INFO(...)		::GameEngine::Log::GetApplicationLogger()->info(__VA_ARGS__)
#define APPLICATION_DEBUG(...)		::GameEngine::Log::GetApplicationLogger()->debug(__VA_ARGS__)
#define APPLICATION_TRACE(...)		::GameEngine::Log::GetApplicationLogger()->trace(__VA_ARGS__)