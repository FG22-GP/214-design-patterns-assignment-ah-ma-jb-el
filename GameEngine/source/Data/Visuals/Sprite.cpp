#include "Core.hpp"
#include "Sprite.hpp"

#include "Engine/Renderer/Renderer.hpp"
#include "SDL_image.h"
#include "SDL.h"

namespace GameEngine
{
// CONSTRUCTORS

	Sprite::Sprite(std::shared_ptr<SDL_Texture> texture){
		m_Texture = texture;
	}

	Sprite::Sprite(std::shared_ptr<Renderer> renderer, const std::string& filepath){
		auto* surface = IMG_Load(filepath.c_str());
		
		auto* texture = SDL_CreateTextureFromSurface(
			*renderer, surface
		);
		m_Texture.reset(texture);
	}

}