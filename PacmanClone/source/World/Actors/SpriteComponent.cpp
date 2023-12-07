#include "PacmanCore.h"
#include "SpriteComponent.hpp"

#include "Data/Visuals/Sprite.hpp"
#include "Actor.hpp"

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

const Texture& SpriteComponent::GetTexture()
{
	return LoadedSprite->GetTexture();
}
const Rectangle& SpriteComponent::GetCrop()
{
	return LoadedSprite->GetCrop();
}

double SpriteComponent::GetRotation()
{
	return GetParent()->ActorTransform.GetRotation() +
		LoadedSprite->GetRotation();
}
const Point2& SpriteComponent::GetCentre()
{
	return LoadedSprite->GetCentre();
}
RenderFlip SpriteComponent::GetFlip()
{
	return LoadedSprite->GetFlip();
}
const Vector2& SpriteComponent::GetWorldLocation()
{
	return Parent->ActorTransform.GetLocation();
}
const Vector2& SpriteComponent::GetWorldScale()
{
	return Parent->ActorTransform.GetScale();
}