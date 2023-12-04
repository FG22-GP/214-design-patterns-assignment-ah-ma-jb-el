#include "Core.hpp"
#include "SpriteComponent.hpp"

namespace GameEngine
{
	void SpriteComponent::Initialize(std::shared_ptr<Sprite> SpriteObject)
	{
		LoadedSprite = SpriteObject;
	}

	void Sprite::LoadFromFile(SDL_Renderer* Renderer, const char* FilePath)
	{
		SDL_Surface* Surface = IMG_Load(FilePath);
		Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
		SDL_FreeSurface(Surface);
	}
}