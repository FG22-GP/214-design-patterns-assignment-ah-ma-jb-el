#include "Core.hpp"
#include "Point2.hpp"

#include "SDL.h"

namespace GameEngine
{
// CONSTRUCTORS

	Point2::Point2() : 
		m_Point(new SDL_Point()){}

	Point2::Point2(const uint32_t x, const uint32_t y){
		m_Point.reset(new SDL_Point());
		m_Point->x = x;
		m_Point->y = y;
	}

	Point2::Point2(const Point2& point) :
		m_Point(new SDL_Point(*point.m_Point)){}

	Point2::Point2(const SDL_Point& point) :
		m_Point(new SDL_Point(point)){}

	Point2::~Point2() = default;

// PRESETS

	Directions Point2::Direction(Point2 DirectionVector)
	{
		if(DirectionVector == Point2::Up())
			return Directions::Up;
		if(DirectionVector == Point2::Down())
			return Directions::Down;
		if(DirectionVector == Point2::Right())
			return Directions::Right;
		if(DirectionVector == Point2::Left())
			return Directions::Left;

		return Directions::None;
	}

	Point2 Point2::DirectionVector(Directions Dir){
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

	std::vector<Point2> Point2::AllDirections(){
		std::vector<Point2> Directions;
		Directions.push_back(Up());
		Directions.push_back(Down());
		Directions.push_back(Right());
		Directions.push_back(Left());
		return Directions;
	}

	bool Point2::IsOpposingDirection(Directions dir1, Directions dir2)
	{
		return (dir1 == Directions::Up && dir2 == Directions::Down) ||
			(dir1 == Directions::Down && dir2 == Directions::Up) ||
			(dir1 == Directions::Right && dir2 == Directions::Left) ||
			(dir1 == Directions::Left && dir2 == Directions::Right);
	}

	Directions Point2::GetOppositeDirection(Directions dir)
	{
		switch (dir) {
		case Directions::Up:
			return Directions::Down;
		case Directions::Down:
			return Directions::Up;
		case Directions::Right:
			return Directions::Left;
		case Directions::Left:
			return Directions::Right;
		default:
			return Directions::None;
		}
	}

	Point2 Point2::GetPoint2InDirection(Point2 point, Directions dir, uint32_t distance)
	{
		switch (dir) {
		case Directions::Up: // Bugged in real pacman game, keeping it for flavour
			return Point2(point.GetX() - distance, point.GetY() - distance); 
		case Directions::Down:
			return Point2(point.GetX(), point.GetY() + distance);
		case Directions::Right:
			return Point2(point.GetX() + distance, point.GetY());
		case Directions::Left:
			return Point2(point.GetX() - distance, point.GetY());
		default:
			return Point2(point.GetX(), point.GetY());
		}
	}

	// GETTERS

	int32_t Point2::GetX() const {
		return m_Point->x;
	}

	int32_t Point2::GetY() const {
		return m_Point->y;
	}


	SDL_Point* Point2::ToSDL() const{
		return m_Point.get();
	}

// SETTERS

	void Point2::SetX(const uint32_t x){
		m_Point->x = x;
	}

	void Point2::SetY(const uint32_t y){
		m_Point->y = y;
	}

	void Point2::Set(const uint32_t x, const uint32_t y){
		SetX(x);
		SetY(y);
	}

// OPERATORS

	bool Point2::operator==(const Point2& other) const {
		return (m_Point->x == other.GetX()) && 
			   (m_Point->y == other.GetY());
	}

	Point2 Point2::operator + (const Point2& other) const {
		return Point2(
			m_Point->x + other.GetX(),
			m_Point->y + other.GetY()
		);
	}

	Point2 Point2::operator - (const Point2& other) const {
		return Point2(
			m_Point->x - other.GetX(),
			m_Point->y - other.GetY()
		);
	}

	Point2& Point2::operator = (const Point2& other){
		m_Point->x = other.GetX();
		m_Point->y = other.GetY();
		return *this;
	}


	Point2::operator SDL_Point* (){
		return m_Point.get();
	}

	Point2 Point2::Rotate90DegreesClockwise(const Point2& point)
	{
		const int X = -point.GetY();
		const int Y = point.GetX();
		return Point2(X, Y);
	}

	Point2 Point2::Rotate90DegreesCounterClockwise(const Point2& point)
	{
		const int X = point.GetY();
		const int Y = -point.GetX();
		return Point2(X, Y);
	}

	Directions Point2::Rotate90DegreesClockwise(Directions Dir)
	{
		switch (Dir) {
		case Directions::Up:
			return Directions::Right;
		case Directions::Down:
			return Directions::Left;
		case Directions::Right:
			return Directions::Down;
		case Directions::Left:
			return Directions::Up;
		default:
			return Directions::None;
		}
	}

	Directions Point2::Rotate90DegreesCounterClockwise(Directions Dir)
	{
		switch (Dir) {
		case Directions::Up:
			return Directions::Left;
		case Directions::Down:
			return Directions::Right;
		case Directions::Right:
			return Directions::Up;
		case Directions::Left:
			return Directions::Down;
		default:
			return Directions::None;
		}
	}

	void Point2::Deleter::operator()(SDL_Point* p) const noexcept {
		p = nullptr;
	}

}