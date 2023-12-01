#include "Core.hpp"
#include "Application.hpp"

#include "SDL.h"

namespace GameEngine
{
	void Application::Init(){
		// TO DO: Include bool params for additional includes, like audio
		SDL_Init(SDL_INIT_VIDEO);
	}

	void Application::Quit(){
		SDL_Quit();
	}
}