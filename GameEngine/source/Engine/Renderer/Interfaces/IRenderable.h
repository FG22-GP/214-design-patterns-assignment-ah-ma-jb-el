#pragma once

#include "Core.hpp"
#include "SDL.h"

namespace GameEngine
{
	struct Texture;

	class IRenderable
	{
	public:

		virtual Texture* GetTexture() = 0;
		virtual SDL_Rect* GetCrop() = 0;
		virtual SDL_Rect* GetRect() = 0;
		virtual double GetRotation() = 0;
		virtual SDL_Point* GetCentre() = 0;
		virtual SDL_RendererFlip GetFlip() = 0;

	};
}


