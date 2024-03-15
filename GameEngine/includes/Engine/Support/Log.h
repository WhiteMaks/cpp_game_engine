#pragma once

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "Core.h"

namespace GameEngine
{

	class GAME_ENGINE_API Log
	{

	private:
		static std::shared_ptr<spdlog::logger> engineLogger;
		static std::shared_ptr<spdlog::logger> applicationLogger;

	public:
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger()
		{
			return engineLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& GetApplicationLogger()
		{
			return applicationLogger;
		}

		static void Init();
	};

}

#define GAME_ENGINE_CRITICAL(...)	::GameEngine::Log::GetEngineLogger()->critical(__VA_ARGS__)
#define GAME_ENGINE_ERROR(...)		::GameEngine::Log::GetEngineLogger()->error(__VA_ARGS__)
#define GAME_ENGINE_WARNING(...)	::GameEngine::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define GAME_ENGINE_INFO(...)		::GameEngine::Log::GetEngineLogger()->info(__VA_ARGS__)
#define GAME_ENGINE_DEBUG(...)		::GameEngine::Log::GetEngineLogger()->debug(__VA_ARGS__)
#define GAME_ENGINE_TRACE(...)		::GameEngine::Log::GetEngineLogger()->trace(__VA_ARGS__)

#define APPLICATION_CRITICAL(...)	::GameEngine::Log::GetApplicationLogger()->critical(__VA_ARGS__)
#define APPLICATION_ERROR(...)		::GameEngine::Log::GetApplicationLogger()->error(__VA_ARGS__)
#define APPLICATION_WARNING(...)	::GameEngine::Log::GetApplicationLogger()->warn(__VA_ARGS__)
#define APPLICATION_INFO(...)		::GameEngine::Log::GetApplicationLogger()->info(__VA_ARGS__)
#define APPLICATION_DEBUG(...)		::GameEngine::Log::GetApplicationLogger()->debug(__VA_ARGS__)
#define APPLICATION_TRACE(...)		::GameEngine::Log::GetApplicationLogger()->trace(__VA_ARGS__)