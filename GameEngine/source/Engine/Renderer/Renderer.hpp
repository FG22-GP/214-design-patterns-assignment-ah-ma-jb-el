#pragma once

#include "Core.hpp"
#include "SDL.h"

namespace GameEngine
{
	class Renderer
	{
	public:

		GAME_API static void StartDrawing();
		GAME_API static void StopDrawing();

		GAME_API static void Clean();

	private:

		static SDL_Renderer* s_Renderer;

	};
}