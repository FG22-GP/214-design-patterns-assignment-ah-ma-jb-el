#include "Core.hpp"
#include "Window.hpp"

#include "SDL.h"

namespace GameEngine
{
	void GameEngine::Window::Create(const std::string& title, const uint32_t width, const uint32_t height){
		SDL_Init(SDL_INIT_VIDEO);

		SDL_CreateWindow(
			title.c_str(), 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			width, height, 
			SDL_WINDOW_SHOWN
		);
	}
}