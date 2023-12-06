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

		GAME_API SDL_Texture* ToSDL() const;

		GAME_API operator SDL_Texture* ();

	private:

		struct Deleter { void operator()(SDL_Texture*) const noexcept; };
		std::unique_ptr<SDL_Texture, Deleter> m_Texture;

	};
}