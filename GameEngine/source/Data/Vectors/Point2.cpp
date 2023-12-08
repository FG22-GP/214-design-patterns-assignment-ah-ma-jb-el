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

	void Point2::Deleter::operator()(SDL_Point* p) const noexcept {
		p = nullptr;
	}

}