#pragma once

#include "Core.hpp"

struct SDL_Point;

namespace GameEngine
{
	enum Directions
	{
		Up	  = 0,
		Down  = 1,
		Right = 2,
		Left  = 3
	};
	struct Point2
	{
	public:

		GAME_API Point2();
		GAME_API Point2(const uint32_t x, const uint32_t y);
		GAME_API Point2(const SDL_Point& point);
		GAME_API Point2(const Point2&);
		GAME_API ~Point2();

	// PRESETS

		GAME_API static Point2 Up();
		GAME_API static Point2 Down();
		GAME_API static Point2 Right();
		GAME_API static Point2 Left();
		GAME_API static Point2 DirectionVector(Directions Dir);
		GAME_API static std::vector<Point2> AllDirections();

	// GETTERS
	
		GAME_API int32_t GetX() const;
		GAME_API int32_t GetY() const;

		GAME_API SDL_Point* ToSDL() const;

	// SETTERS
	
		GAME_API void SetX(const uint32_t x);
		GAME_API void SetY(const uint32_t y);
		GAME_API void Set(const uint32_t x, const uint32_t y);

	// OPERATORS

		GAME_API bool operator == (const Point2& other) const;
		GAME_API Point2 operator + (const Point2& other) const;
		GAME_API Point2 operator - (const Point2& other) const;
		GAME_API Point2& operator = (const Point2& other);

		GAME_API operator SDL_Point* ();

	private:

		struct Deleter { void operator ()(SDL_Point*) const noexcept; };
		std::unique_ptr<SDL_Point, Deleter> m_Point;

	};
}