#include "Core.hpp"
#include "Texture.hpp"

#include "Engine/Renderer/Renderer.hpp"
#include "SDL_image.h"
#include "SDL.h"

namespace GameEngine
{
	Texture::Texture(std::shared_ptr<Renderer> renderer, const std::string& filepath){
		auto* surface = IMG_Load(filepath.c_str());

		auto* texture = SDL_CreateTextureFromSurface(
			*renderer, surface
		);
		m_Texture.reset(texture);
	}

// GETTERS

	SDL_Texture* Texture::GetSDL() const { 
		return m_Texture.get();
	}

// OPERATORS

	Texture::operator SDL_Texture* (){ 
		return m_Texture.get(); 
	}

	void Texture::Deleter::operator()(SDL_Texture* t) const noexcept {
		SDL_DestroyTexture(t);
	}

}