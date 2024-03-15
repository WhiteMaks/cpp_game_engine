#pragma once

#ifdef GAME_ENGINE_PLATFORM_WINDOWS
	#ifdef GAME_ENGINE_BUILD_DLL
		#define GAME_ENGINE_API __declspec(dllexport)
	#else
		#define GAME_ENGINE_API __declspec(dllimport)
	#endif
#elif GAME_ENGINE_PLATFORM_BROWSER
	#ifdef GAME_ENGINE_BUILD_DLL
		#define GAME_ENGINE_API
	#else
		#define GAME_ENGINE_API
	#endif
#else
	#error Game Engine only supports Windows and Browser!
#endif
