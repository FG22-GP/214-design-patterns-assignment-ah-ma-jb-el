#include "Core.hpp"
#include "World.hpp"
#include "Actor.hpp"

void World::RegisterActor(std::shared_ptr<Actor> NewActor)
{
	RegisteredActors.push_back(NewActor);
}

void World::TickAllRegisteredActors(float DeltaTime)
{
	for (std::shared_ptr<Actor> RegisteredActor: RegisteredActors)
	{
		RegisteredActor->Tick(DeltaTime);
	}
}

template<typename T> std::shared_ptr<T> World::CreateActor()
{
	static_assert(std::is_base_of<Actor, T>::value,
		"T must be derived from Actor");
	std::shared_ptr<T> NewActor = std::make_shared<T>(shared_from_this());
	RegisterActor(NewActor);
	return NewActor;
}