#include "Core.hpp"
#include "SpriteComponent.hpp"
#include "Actor.hpp"

namespace GameEngine
{
	std::vector<std::shared_ptr<SpriteComponent>> SpriteComponent::AllSpriteComponents;


	void SpriteComponent::Initialize(std::shared_ptr<Sprite> SpriteObject)
	{
		LoadedSprite = SpriteObject;
		AllSpriteComponents.push_back(shared_from_this());
	}

	Vector2 SpriteComponent::GetPosition()
	{
		return Parent->ActorTransform.GetLocation();
	}

	float SpriteComponent::GetScale()
	{
		return Parent->ActorTransform.GetScale();
	}

	Sprite::Sprite(SDL_Renderer* Renderer, const char* FilePath)
	{
		SDL_Surface* Surface = IMG_Load(FilePath);
		Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
		SDL_FreeSurface(Surface);
	}
}