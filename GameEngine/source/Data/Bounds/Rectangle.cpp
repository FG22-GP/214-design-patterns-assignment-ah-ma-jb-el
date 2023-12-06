#include "Core.hpp"
#include "Rectangle.hpp"

#include "Data/Vectors/Point2.hpp"
#include "SDL.h"

namespace GameEngine
{
// CONSTRUCTORS

	Rectangle::Rectangle(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height){
		m_Rect.reset(new SDL_Rect());
		m_Rect->x = x;
		m_Rect->y = y;
		m_Rect->w = width;
		m_Rect->h = height;
	}

	Rectangle::Rectangle(const SDL_Rect& rect) : 
		m_Rect(new SDL_Rect(rect)){}

// GETTERS

	uint32_t Rectangle::GetX() const {
		return m_Rect->x;
	}

	uint32_t Rectangle::GetY() const {
		return m_Rect->y;
	}

	Point2 Rectangle::GetPosition() const {
		return Point2(GetX(), GetY());
	}
	

	uint32_t Rectangle::GetWidth() const {
		return m_Rect->w;
	}

	uint32_t Rectangle::GetHeight() const {
		return m_Rect->h;
	}

	Point2 Rectangle::GetSize() const {
		return Point2(GetWidth(), GetHeight());
	}


	SDL_Rect* Rectangle::ToSDL() const {
		return m_Rect.get();
	}

// SETTERS

	void Rectangle::SetX(const uint32_t x){
		m_Rect->x = x;
	}

	void Rectangle::SetY(const uint32_t y){
		m_Rect->y = y;
	}

	void Rectangle::SetPosition(const uint32_t x, const uint32_t y){
		SetX(x); 
		SetY(y);
	}


	void Rectangle::SetWidth(const uint32_t width){
		m_Rect->w = width;
	}

	void Rectangle::SetHeight(const uint32_t height){
		m_Rect->h = height;
	}

	void Rectangle::SetSize(const uint32_t width, const uint32_t height){
		SetWidth(width); 
		SetHeight(height);
	}

// OPERATORS

	Rectangle::operator struct SDL_Rect* (){
		return m_Rect.get();
	}

	Rectangle::operator struct SDL_Rect& (){
		return *m_Rect;
	}

	void Rectangle::Deleter::operator()(SDL_Rect*) const noexcept {

	}

}