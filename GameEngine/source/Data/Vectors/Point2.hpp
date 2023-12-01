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

		static Point2 Up() {
			Point2 P;
			P.x = 0; P.y = 1;
			return P;
		}

		static Point2 Down() {
			Point2 P;
			P.x = 0; P.y = -1;
			return P;
		}

		static Point2 Right() {
			Point2 P;
			P.x = 1; P.y = 0;
			return P;
		}

		static Point2 Left() {
			Point2 P;
			P.x = -1; P.y = 0;
			return P;
		}

		static Point2 DirectionVector(Directions Dir)
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
				return Point2();
			}
		}

#pragma endregion

	};
}