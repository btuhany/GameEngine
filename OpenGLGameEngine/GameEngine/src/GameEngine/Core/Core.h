#pragma once

#ifdef GAME_ENGINE_WINDOWS
	#ifdef GAME_ENGINE_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif // GAME_ENGINE_BUILD_DLL
#else
	#error This game engine supports only WINDOWS!
#endif // GAME_ENGINE_WINDOWS
