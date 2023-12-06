#pragma once

#include "Core.hpp"
#include "SDL.h"

namespace GameEngine
{
	struct Texture;
	struct Rectangle;

	class IRenderable
	{
	public:

		virtual const Texture& GetTexture() = 0;
		virtual const Rectangle& GetCrop() = 0;
		virtual const Rectangle& GetRect() = 0;
		virtual double GetRotation() = 0;
		virtual SDL_Point* GetCentre() = 0;
		virtual SDL_RendererFlip GetFlip() = 0;

	};
}


