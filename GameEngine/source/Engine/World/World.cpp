#include "Core.hpp"
#include "World.hpp"
#include "Actor.hpp"

void World::RegisterActor(std::shared_ptr<Actor> NewActor)
{
	RegisteredActors.push_back(NewActor);
}

std::shared_ptr<Actor> World::CreateActor()
{
	std::shared_ptr<Actor> NewActor = std::make_shared<Actor>(shared_from_this());
	RegisterActor(NewActor);
	return NewActor;
}

void World::TickAllRegisteredActors(float DeltaTime)
{
	for (std::shared_ptr<Actor> RegisteredActor: RegisteredActors)
	{
		RegisteredActor->Tick(DeltaTime);
	}
}
