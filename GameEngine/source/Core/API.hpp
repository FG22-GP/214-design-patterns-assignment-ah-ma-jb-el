#pragma once

#if defined(_WIN32)
	#ifdef GAME_ENGINE
		#define GAME_API __declspec(dllexport)
	#else
		#define GAME_API __declspec(dllimport)
	#endif
#elif
	#error Platform not supported
#endif