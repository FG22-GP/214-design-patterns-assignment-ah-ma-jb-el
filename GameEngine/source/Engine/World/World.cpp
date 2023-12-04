#include "Core.hpp"
#include "World.hpp"
#include "Actors/Actor.hpp"
#include "Data/Transform.hpp"

namespace GameEngine
{
	void World::Tick(float DeltaTime)
	{
		TickAllRegisteredActors(DeltaTime);

		RenderAllRegisteredActors();
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
		//TODO
	}

	template<typename T> std::shared_ptr<T> World::CreateActor()
	{
		static_assert(std::is_base_of<Actor, T>::value,
			"T must be derived from Actor");
		std::shared_ptr<T> NewActor = std::make_shared<T>(shared_from_this());
		RegisterActor(NewActor);
		return NewActor;
	}

	template<typename T> std::shared_ptr<T> World::CreateActor(Transform Transform)
	{
		std::shared_ptr<T> NewActor = CreateActor<T>();
		NewActor->ActorTransform = Transform;
		return NewActor;
	}
}