#include "Core.hpp"
#include "Sprite.hpp"

#include "Data/Enums/RenderFlip.hpp"
#include "Data/Vectors/Point2.hpp"
#include "Data/Bounds/Rectangle.hpp"
#include "Data/Visuals/Texture.hpp"
#include "Engine/Renderer/Renderer.hpp"

#include "SDL_image.h"
#include "SDL.h"

namespace GameEngine
{
// CONSTRUCTORS

	Sprite::Sprite(std::shared_ptr<Texture> texture, const Rectangle& crop, const Rectangle& rect, const Point2& centre, const RenderFlip flip, const double rotation) :
		m_Texture(texture),
		m_Crop(new Rectangle(crop)),
		m_Rect(new Rectangle(rect)),
		m_Centre(new Point2(centre)),
		m_Flip(flip),
		m_Rotation(rotation){}

// GETTERS

	double Sprite::GetRotation() const {
		return m_Rotation;
	}

	RenderFlip Sprite::GetFlip() const {
		return m_Flip;
	}

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