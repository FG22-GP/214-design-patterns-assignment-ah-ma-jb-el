#include "Core.hpp"
#include "Application.hpp"

#include "SDL.h"

namespace GameEngine
{
	void Application::Init(){
		// TODO: Include bool params for additional includes, like audio
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		{
			// TODO: Log init errors
		}

	}

	void Application::Quit(){
		SDL_Quit();
	}
}