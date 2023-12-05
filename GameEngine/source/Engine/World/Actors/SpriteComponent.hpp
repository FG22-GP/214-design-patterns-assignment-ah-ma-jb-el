#pragma once

#include "Core.hpp"
#include "ActorComponent.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_render.h>
#include <Data/Vectors/Vector2.hpp>

namespace GameEngine
{
	class World;
	class Sprite;

	class SpriteComponent : public ActorComponent, public std::enable_shared_from_this<SpriteComponent>
	{
		friend class World;

	public:
		GAME_API void Initialize(std::shared_ptr<Sprite> SpriteObject);


		GAME_API Vector2 GetPosition();
		GAME_API float GetScale();

	protected:
		std::shared_ptr<Sprite> LoadedSprite;

		static std::vector<std::shared_ptr<SpriteComponent>> AllSpriteComponents;
		
	};
}
