#pragma once

#include "Core.hpp"

namespace GameEngine
{
	enum Directions
	{
		Up = 0,
		Down = 1,
		Right = 2,
		Left = 3
	};

	struct GAME_API Point2
	{
		int32_t x;
		int32_t y;

#pragma region Static Directions

		static Point2 Up();
		static Point2 Down();
		static Point2 Right();
		static Point2 Left();
		static Point2 DirectionVector(Directions Dir);
		static std::vector<Point2> AllDirections();

#pragma endregion

	};
}