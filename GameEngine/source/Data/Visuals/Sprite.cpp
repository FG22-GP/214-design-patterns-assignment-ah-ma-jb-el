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

	Sprite::Sprite(const Sprite& sprite) :
		m_Texture(sprite.m_Texture),
		m_Crop(new Rectangle(*sprite.m_Crop.get())),
		m_Rect(new Rectangle(*sprite.m_Rect.get())),
		m_Centre(new Point2(*sprite.m_Centre.get())),
		m_Flip(sprite.m_Flip),
		m_Rotation(sprite.m_Rotation){}

	Sprite::~Sprite() = default;

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

	Sprite& Sprite::operator=(const Sprite& other){
		m_Texture = other.m_Texture;

		m_Crop.release();
		m_Crop.reset(new Rectangle(*other.m_Crop));	
		
		m_Rect.release();
		m_Rect.reset(new Rectangle(*other.m_Rect));

		m_Centre.release();
		m_Centre.reset(new Point2(*other.m_Centre));

		m_Flip	   = other.m_Flip;
		m_Rotation = other.m_Rotation;

		return *this;
	}


	void Sprite::CropDeleter::operator()(Rectangle* r) const noexcept { delete(r); }

	void Sprite::RectDeleter::operator()(Rectangle* r) const noexcept { delete(r); }

	void Sprite::CentreDeleter::operator()(Point2* p) const noexcept { delete(p); }

}