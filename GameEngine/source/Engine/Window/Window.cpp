#include "Core.hpp"
#include "Window.hpp"

namespace GameEngine
{
	SDL_Window* Window::s_Window;

// SINGLETON

	/*Window& Window::GetInstance(){
		static Window instance;
		return instance;
	}*/

// CONSTRUCTORS

	/*Window::Window() :
		m_Window(nullptr) {}*/

	/*Window::~Window(){
		SDL_DestroyWindow(s_Window);
	}*/

// WINDOW

	void GameEngine::Window::Create(const std::string& title, const uint32_t width, const uint32_t height){
		SDL_Init(SDL_INIT_VIDEO);

		//auto instance = GetInstance();

		s_Window = SDL_CreateWindow(
			title.c_str(), 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			width, height, 
			SDL_WINDOW_SHOWN
		);
	}

	void Window::Close(){
		SDL_DestroyWindow(s_Window);
		SDL_Quit();
	}
}