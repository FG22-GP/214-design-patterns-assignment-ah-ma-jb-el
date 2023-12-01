#pragma once

#include "Core.hpp"
//#include "SDL.h"

namespace GameEngine
{
	struct SDL_Renderer;

	class Renderer
	{
	public:

		GAME_API static void StartDrawing();
		GAME_API static void StopDrawing();

		GAME_API static void Clean();

	private:

		SDL_Renderer* m_Renderer;

	};
}