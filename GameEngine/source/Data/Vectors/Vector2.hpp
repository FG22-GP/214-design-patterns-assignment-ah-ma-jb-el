#pragma once

#include "Core.hpp"

namespace GameEngine
{
	struct Point2;

	struct Vector2
	{
		float X, Y;

		GAME_API Vector2();
		GAME_API Vector2(const Point2& Point);
		GAME_API Vector2(int X, int Y);

		GAME_API Vector2 operator+(const Vector2& other) const;

		GAME_API void operator+=(const Vector2& other);

		GAME_API Vector2 operator-(const Vector2& other) const;

		GAME_API void operator-=(const Vector2& other);

		GAME_API bool operator==(const Vector2& other) const;

		GAME_API Vector2 operator/(const float& other) const;

		GAME_API Vector2 operator*(const float& other) const;

		GAME_API static Vector2 Lerp(const Vector2& A, const Vector2& B, float Alpha);
		
		// Gives you a Vector where X and Y are individually inverselerped. No clamping.
		GAME_API static Vector2 InverseLerpByAxis(const Vector2& A, const Vector2& B, const Vector2& Point);
	};
}
