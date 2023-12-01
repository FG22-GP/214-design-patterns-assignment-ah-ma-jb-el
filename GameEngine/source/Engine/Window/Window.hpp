#pragma once

#include "Core.hpp"

namespace GameEngine
{
	class Window
	{
	public:

		GAME_API Window();
		GAME_API ~Window();

		GAME_API static void Create(const std::string& title, const uint32_t width, const uint32_t height);

	private:

		//static SDL_Window s_Window;

	};
}