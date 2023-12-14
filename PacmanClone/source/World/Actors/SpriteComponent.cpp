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

void SpriteComponent::SetLocalFlip(RenderFlip flip){
	SpriteFlip = flip;
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
	auto rotation = GetParent()->ActorTransform.GetRotation() +
		LoadedSprite->GetRotation();

	//We adjust rotations outside [-90..90] so the GetFlip() function can flip instead.
	if (rotation > 90.0f)
		return rotation - 180.0f;
	if (rotation <= -90.0f)
		return rotation + 180.0f;
	return rotation;
}
const Point2& SpriteComponent::GetCentre()
{
	return LoadedSprite->GetCentre();
}
RenderFlip SpriteComponent::GetFlip()
{
	if (SpriteFlip != RenderFlip::None)
		return SpriteFlip;

	//We flip when we adjust rotations in GetRotation()
	if (GetParent()->ActorTransform.GetRotation() <= -90.0f ||
		GetParent()->ActorTransform.GetRotation() > 90.0f)
	{
		return RenderFlip::Horizontally;
	}

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