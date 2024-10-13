#pragma once


#ifdef GAME_ENGINE_WINDOWS
	#ifdef GAME_ENGINE_USE_DYNAMIC_LIB
		#ifdef GAME_ENGINE_BUILD_DLL
			#define ENGINE_API __declspec(dllexport)
		#else
			#define ENGINE_API __declspec(dllimport)
		#endif // GAME_ENGINE_BUILD_DLL
	#else
		#define ENGINE_API
	#endif // GAME_ENGINE_USE_DYNAMIC_LIB
#else
	#error This game engine supports only WINDOWS!
#endif // GAME_ENGINE_WINDOWS
