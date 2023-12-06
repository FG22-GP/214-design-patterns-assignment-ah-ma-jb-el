#pragma once

#include "Core.hpp"

struct SDL_Rect;

namespace GameEngine
{
	struct Rectangle
	{
	public:

		GAME_API Rectangle(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height);
		GAME_API Rectangle(const SDL_Rect& rect);

	// GETTERS

		GAME_API uint32_t GetX() const;
		GAME_API uint32_t GetY() const;
		GAME_API uint32_t GetWidth() const;
		GAME_API uint32_t GetHeight() const;

		GAME_API SDL_Rect* ToSDL() const;

	// OPERATORS

		GAME_API operator struct SDL_Rect* ();
		GAME_API operator struct SDL_Rect& ();

	private:

		struct Deleter { void operator()(SDL_Rect*) const noexcept; };
		std::unique_ptr<SDL_Rect, Deleter> m_Rect;

	};
}