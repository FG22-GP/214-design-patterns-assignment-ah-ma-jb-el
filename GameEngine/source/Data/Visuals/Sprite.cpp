#include "Core.hpp"
#include "Sprite.hpp"

#include "Data/Visuals/Texture.hpp"
#include "Data/Bounds/Rectangle.hpp"
#include "Data/Vectors/Point2.hpp"
#include "Engine/Renderer/Renderer.hpp"
#include "SDL_image.h"
#include "SDL.h"

namespace GameEngine
{
// CONSTRUCTORS

	Sprite::Sprite(std::shared_ptr<Texture> texture) :
		m_Rotation(0), m_Flip(0), m_Texture(texture),
		m_Crop(new Rectangle(0, 0, 0, 0)),
		m_Rect(new Rectangle(0, 0, 0, 0)),
		m_Centre(new Point2({0, 0})){}

// GETTERS

	const Texture& Sprite::GetTexture() const { 
		return *m_Texture; 
	}

	const Rectangle& Sprite::GetCrop() const {
		return *m_Crop;
	}

	const Rectangle& Sprite::GetRect() const {
		return *m_Rect;
	}

	const Point2& Sprite::GetCentre() const {
		return *m_Centre;
	}

// OPERATORS

	void Sprite::CropDeleter::operator()(Rectangle* r) const noexcept { delete r; }

	void Sprite::RectDeleter::operator()(Rectangle* r) const noexcept { delete r; }

	void Sprite::CentreDeleter::operator()(Point2* p) const noexcept { delete p; }

}