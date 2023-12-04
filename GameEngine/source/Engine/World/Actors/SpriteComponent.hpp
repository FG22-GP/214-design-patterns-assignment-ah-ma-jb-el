#pragma once

#include "Core.hpp"
#include "ActorComponent.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_render.h>

namespace GameEngine
{
	struct Sprite
	{
	public:

		void LoadFromFile(SDL_Renderer* Renderer, const char* FilePath);

	protected:

		SDL_Texture* Texture;
	};


	class SpriteComponent : public ActorComponent
	{
		void Initialize(std::shared_ptr<Sprite> SpriteObject);

	protected:

		std::shared_ptr<Sprite> LoadedSprite;
	};
}
