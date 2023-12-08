#pragma once

#include "Core.hpp"

#include <assert.h>

#include "Point2.hpp"

namespace GameEngine
{
	struct Point2;

	struct Vector2
	{
		float X, Y;

		GAME_API Vector2();
		GAME_API Vector2(const Point2& Point);
		GAME_API Vector2(int X, int Y);
		GAME_API Vector2(float X, float Y);

		GAME_API static Vector2 Up() { return {0.0f, -1.0f}; }
		GAME_API static Vector2 Down() { return {0.0f, 1.0f}; }
		GAME_API static Vector2 Right() { return {1.0f, 0.0f}; }
		GAME_API static Vector2 Left() { return {-1.0f, 0.0f}; }
		GAME_API static Vector2 Zero() { return {0.0f, 0.0f}; }
		GAME_API static Vector2 One() { return {1.0f, 1.0f}; }
		GAME_API static Vector2 Direction(Directions Dir)
		{
			switch (Dir)
			{
			case Directions::Up:
				return Up();
			case Directions::Down:
				return Down();
			case Directions::Right:
				return Right();
			case Directions::Left:
				return Left();
			default:
				assert(false &&  "Unhandles Direction in Vector2::Direction");
				return Zero();
			}
		}

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

		// Gives you a float of the distance between two points.
		GAME_API static float Distance(const Vector2& A, const Vector2& B);

		// Gives you a float of the distance between two points, squared.
		GAME_API static float DistanceSquared(const Vector2& A, const Vector2& B);
	};
}
