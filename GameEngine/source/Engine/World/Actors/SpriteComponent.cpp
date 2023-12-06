#include "Core.hpp"
#include "SpriteComponent.hpp"

#include "Data/Visuals/Sprite.hpp"
#include "Actor.hpp"

namespace GameEngine
{
	std::vector<std::shared_ptr<SpriteComponent>> SpriteComponent::AllSpriteComponents;


	void SpriteComponent::Initialize(std::shared_ptr<Sprite> SpriteObject)
	{
		LoadedSprite = SpriteObject;
		AllSpriteComponents.push_back(std::shared_ptr<SpriteComponent>(this));
	}

	Vector2 SpriteComponent::GetPosition()
	{
		return Parent->ActorTransform.GetLocation();
	}

	float SpriteComponent::GetScale()
	{
		return Parent->ActorTransform.GetScale();
	}
	const Texture& SpriteComponent::GetTexture()
	{
		return LoadedSprite->GetTexture();
	}
	const Rectangle& SpriteComponent::GetCrop()
	{
		//TODO
		return LoadedSprite->GetCrop();
	}
	const Rectangle& SpriteComponent::GetRect()
	{
		return LoadedSprite->GetRect();
	}
	double SpriteComponent::GetRotation()
	{
		return GetParent()->ActorTransform.GetRotation();
	}
	SDL_Point* SpriteComponent::GetCentre()
	{
		//TODO
		return nullptr;
	}
	SDL_RendererFlip SpriteComponent::GetFlip()
	{
		//TODO
		return SDL_RendererFlip();
	}
}