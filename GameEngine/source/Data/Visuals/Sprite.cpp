#include "Core.hpp"
#include "Sprite.hpp"

#include "Engine/Renderer/Renderer.hpp"
#include "Data/Visuals/Texture.hpp"
#include "SDL_image.h"
#include "SDL.h"

namespace GameEngine
{
// CONSTRUCTORS

	Sprite::Sprite(std::shared_ptr<Texture> texture) :
		m_Rotation(0), m_Flip(0), m_Texture(texture),
		m_Crop(new SDL_Rect({ 0, 0, 0, 0 })),
		m_Rect(new SDL_Rect({ 0, 0, 0, 0 })),
		m_Centre(new SDL_Point({0, 0})){}

// GETTERS

	std::shared_ptr<Texture> Sprite::GetTexture() const { return m_Texture; }

// OPERATORS

	void Sprite::CropDeleter::operator()(SDL_Rect* r) const noexcept { delete r; }

	void Sprite::RectDeleter::operator()(SDL_Rect* r) const noexcept { delete r; }

	void Sprite::CentreDeleter::operator()(SDL_Point* p) const noexcept { delete p; }

}