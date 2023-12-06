#pragma once

#include "Core.hpp"

struct SDL_Texture;

namespace GameEngine
{
	class Renderer;

	struct Texture 
	{
	public:

		GAME_API Texture(std::shared_ptr<Renderer> renderer, const std::string& filepath);
		GAME_API Texture(SDL_Texture* texture);

	// GETTERS

		GAME_API uint32_t GetWidth() const;
		GAME_API uint32_t GetHeight() const;

		GAME_API SDL_Texture* ToSDL() const;

	// OPERATORS

		GAME_API operator SDL_Texture* ();

	private:

		uint32_t m_Width;
		uint32_t m_Height;

		struct Deleter { void operator()(SDL_Texture*) const noexcept; };
		std::unique_ptr<SDL_Texture, Deleter> m_Texture;

	};
}