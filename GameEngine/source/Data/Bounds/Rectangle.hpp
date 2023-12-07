#pragma once

#include "Core.hpp"

struct SDL_Rect;

namespace GameEngine
{
	struct Point2;

	struct Rectangle
	{
	public:

		GAME_API Rectangle(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height);
		GAME_API Rectangle(const Rectangle& rectangle);
		GAME_API Rectangle(const SDL_Rect& rectangle);

	// GETTERS

		GAME_API uint32_t GetX() const;
		GAME_API uint32_t GetY() const;
		GAME_API Point2 GetPosition() const;

		GAME_API uint32_t GetWidth() const;
		GAME_API uint32_t GetHeight() const;
		GAME_API Point2 GetSize() const;

		GAME_API SDL_Rect* ToSDL() const;

	// SETTERS

		GAME_API void SetX(const uint32_t x);
		GAME_API void SetY(const uint32_t y);
		GAME_API void SetPosition(const uint32_t x, const uint32_t y);

		GAME_API void SetWidth(const uint32_t width);
		GAME_API void SetHeight(const uint32_t height);
		GAME_API void SetSize(const uint32_t width, const uint32_t height);

	// OPERATORS

		GAME_API Rectangle& operator = (const Rectangle& other);

		GAME_API operator struct SDL_Rect* ();
		GAME_API operator struct SDL_Rect& ();

	private:

		struct Deleter { void operator()(SDL_Rect*) const noexcept; };
		std::unique_ptr<SDL_Rect, Deleter> m_Rect;

	};
}