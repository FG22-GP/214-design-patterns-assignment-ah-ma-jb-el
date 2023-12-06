#pragma once

#include "Core.hpp"
#include "ActorComponent.hpp"
#include "Engine/Renderer/Interfaces/IRenderable.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_render.h>
#include <Data/Vectors/Vector2.hpp>

namespace GameEngine
{
	class World;
	class Sprite;

	class SpriteComponent : public ActorComponent, public IRenderable
	{
		friend class World;

	public:
		GAME_API void Initialize(std::shared_ptr<Sprite> SpriteObject);


		GAME_API Vector2 GetPosition();
		GAME_API float GetScale();

	protected:
		std::shared_ptr<Sprite> LoadedSprite;

		static std::vector<std::shared_ptr<SpriteComponent>> AllSpriteComponents;
		

		// Inherited via IRenderable
		const Texture& GetTexture() override;
		const Rectangle& GetCrop() override;
		const Rectangle& GetRect() override;
		double GetRotation() override;
		SDL_Point* GetCentre() override;
		SDL_RendererFlip GetFlip() override;

	};
}
