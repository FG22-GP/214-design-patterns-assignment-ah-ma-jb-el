#include "Core.hpp"
#include "Rectangle.hpp"

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

	uint32_t Rectangle::GetWidth() const {
		return m_Rect->w;
	}

	uint32_t Rectangle::GetHeight() const {
		return m_Rect->h;
	}

	SDL_Rect* Rectangle::ToSDL() const {
		return m_Rect.get();
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