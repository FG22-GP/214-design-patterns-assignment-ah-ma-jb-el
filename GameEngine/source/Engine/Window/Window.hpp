#pragma once

#include "Core.hpp"
//#include "SDL.h"

namespace GameEngine
{
	struct SDL_Window;

	class Window
	{
	public:

	// WINDOW

		GAME_API static void Create(const std::string& title, const uint32_t width, const uint32_t height);
		GAME_API static void Close();
			
	// OPERATIONS

		/*Window& operator = (const Window&) = delete;
		Window& operator = (Window&&) = delete;*/

	private:

		SDL_Window* s_Window;

	// CONSTRUCTORS

	//	Window(){};
	//	~Window();

	//	Window(const Window&) = delete;
	//	Window(Window&&) = delete;

	//// SINGLETON

	//	static Window& GetInstance();

	};
}