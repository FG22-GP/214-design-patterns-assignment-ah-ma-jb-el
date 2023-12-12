#include "PacmanCore.h"
#include "World.hpp"
#include "Actors/Actor.hpp"
#include "Data/Transform.hpp"
#include "Actors/SpriteComponent.hpp"
#include "Engine/Window/Window.hpp"
#include "Engine/Renderer/Renderer.hpp"

void World::Tick(float DeltaTime)
{
	TickAllRegisteredActors(DeltaTime);
}

void World::RegisterActor(std::shared_ptr<Actor> NewActor)
{
	RegisteredActors.push_back(NewActor);
}

void World::TickAllRegisteredActors(float DeltaTime)
{
	for (std::shared_ptr<Actor> RegisteredActor : RegisteredActors)
	{
		RegisteredActor->Tick(DeltaTime);
	}
}

void World::RenderAllRegisteredActors()
{
	auto Renderer = GameEngine::Window::GetMain()->GetRenderer();
	if (Renderer == nullptr) return;
	for (auto Comp : SpriteComponent::AllSpriteComponents)
	{
		if (Comp == nullptr)
			continue;
		//TODO At this point, Comp->GetPosition() is in grid-space, not pixel-space.
		Renderer->Draw(*Comp);
	}

}