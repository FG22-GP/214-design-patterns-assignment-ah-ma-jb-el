#pragma once

#include "Core.hpp"

namespace GameEngine
{
	struct Vector2
	{
		float X, Y;

		Vector2 operator+(const Vector2& other) const
		{
			Vector2 Result;
			Result.X = X + other.X;
			Result.Y = Y + other.Y;
			return Result;
		}

		void operator+=(const Vector2& other)
		{
			X += other.X;
			Y += other.Y;
		}

		Vector2 operator-(const Vector2& other) const
		{
			Vector2 Result;
			Result.X = X - other.X;
			Result.Y = Y - other.Y;
			return Result;
		}

		void operator-=(const Vector2& other)
		{
			X -= other.X;
			Y -= other.Y;
		}

		bool operator==(const Vector2& other) const
		{
			return X == other.X && Y == other.Y;
		}
	};
}
