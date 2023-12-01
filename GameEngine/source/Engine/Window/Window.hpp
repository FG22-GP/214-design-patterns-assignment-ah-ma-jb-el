#pragma once

#include "Core.hpp"

struct SDL_Window;

namespace GameEngine
{
	class Window
	{
	public:

		GAME_API static bool IsOpened();

		GAME_API static void Create(const std::string& title, const uint32_t width, const uint32_t height);
		GAME_API static void Close();
		GAME_API static void Clean();

	private:

		bool m_IsOpened;

		struct Deleter { void operator()(SDL_Window*) const noexcept; };
		std::unique_ptr<SDL_Window, Deleter> m_Window;

		Window();
		Window(const Window&) = delete;
		void operator = (const Window&) = delete;

		static Window& GetInstance();

	};
}