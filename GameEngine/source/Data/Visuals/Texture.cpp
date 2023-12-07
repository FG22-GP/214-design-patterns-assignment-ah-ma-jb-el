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
		int width, height;

		SDL_QueryTexture(
			texture, NULL, NULL, 
			&width, &height
		);
		m_Width = width;
		m_Height = height;
	}

	Texture::Texture(const Texture& texture) : 
		m_Texture(texture.m_Texture.get()){
		int width, height;

		SDL_QueryTexture(
			texture.m_Texture.get(), 
			NULL, NULL,
			&width, &height
		);
		m_Width = width;
		m_Height = height;
	}

	Texture::Texture(SDL_Texture* texture) : 
		m_Texture(texture){
		int width, height;

		SDL_QueryTexture(
			texture, NULL, NULL, 
			&width, &height
		);
		m_Width = width;
		m_Height = height;
	}

	Texture::~Texture() = default;

// GETTERS

	uint32_t Texture::GetWidth() const {
		return m_Width;
	}

	uint32_t Texture::GetHeight() const {
		return m_Height;
	}

	SDL_Texture* Texture::ToSDL() const {
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