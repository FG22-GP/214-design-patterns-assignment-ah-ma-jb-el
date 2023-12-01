#include "Core.hpp"
#include "Point2.hpp"

namespace GameEngine
{
#pragma region Static Directions

	std::vector<Point2> Point2::AllDirections()
	{
		std::vector<Point2> Directions;
		Directions.push_back(Up());
		Directions.push_back(Down());
		Directions.push_back(Right());
		Directions.push_back(Left());
		return Directions;
	}

	Point2 Point2::Up()
	{
		Point2 P;
		P.x = 0; P.y = 1;
		return P;
	}

	Point2 Point2::Down()
	{
		Point2 P;
		P.x = 0; P.y = -1;
		return P;
	}

	Point2 Point2::Right()
	{
		Point2 P;
		P.x = 1; P.y = 0;
		return P;
	}

	Point2 Point2::Left()
	{
		Point2 P;
		P.x = -1; P.y = 0;
		return P;
	}

	Point2 Point2::DirectionVector(Directions Dir)
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
}