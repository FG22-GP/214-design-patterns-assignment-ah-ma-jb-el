#pragma once

#include "PacmanCore.h"
#include "ActorComponent.hpp"
#include "Engine/Renderer/Interfaces/IRenderable.h"
#include <Data/Vectors/Vector2.hpp>
#include "Data\Visuals\Sprite.hpp"

using namespace GameEngine;

class World;

class SpriteComponent : public ActorComponent, public IRenderable
{
	friend class World;

public:
	void Initialize(std::shared_ptr<Sprite> SpriteObject);

	SpriteComponent(std::shared_ptr<Actor> ParentActor) : 
		ActorComponent(ParentActor) {}

	Vector2 GetPosition();

protected:
	std::shared_ptr<Sprite> LoadedSprite;

	static std::vector<std::shared_ptr<SpriteComponent>> AllSpriteComponents;


	// Inherited via IRenderable
	const Texture& GetTexture() override;
	const Rectangle& GetCrop() override;
	const Point2& GetCentre() override;
	double GetRotation() override;
	RenderFlip GetFlip() override;
	const Vector2& GetWorldLocation() override;
	const Vector2& GetWorldScale() override;

};