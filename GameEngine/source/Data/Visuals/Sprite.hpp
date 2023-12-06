#pragma once

#include "Core.hpp"

struct SDL_Texture;

namespace GameEngine
{
	class Renderer;

	class Sprite
	{
	public:

		GAME_API Sprite(std::shared_ptr<SDL_Texture> texture);
		GAME_API Sprite(std::shared_ptr<Renderer> renderer, const std::string& filepath);

		GAME_API std::shared_ptr<SDL_Texture> GetTexture() const { return m_Texture; }

	private:

		std::shared_ptr<SDL_Texture> m_Texture;

	};
}