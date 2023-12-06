#pragma once

#include "Core.hpp"

struct SDL_Rect;
struct SDL_Point;

namespace GameEngine
{
	struct Texture;
	class Renderer;

	class Sprite
	{
	public:

		GAME_API Sprite(std::shared_ptr<Texture> texture);

		GAME_API std::shared_ptr<Texture> GetTexture() const;

	private:

		double m_Rotation;
		uint32_t m_Flip;

		std::shared_ptr<Texture> m_Texture;

		struct CropDeleter { void operator()(SDL_Rect*) const noexcept; };
		std::unique_ptr<SDL_Rect> m_Crop;

		struct RectDeleter { void operator()(SDL_Rect*) const noexcept; };
		std::unique_ptr<SDL_Rect> m_Rect;

		struct CentreDeleter { void operator()(SDL_Point*) const noexcept; };
		std::unique_ptr<SDL_Point> m_Centre;

	};
}