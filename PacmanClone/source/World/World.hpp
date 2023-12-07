#pragma once

#include "PacmanCore.h"
#include "Data\Transform.hpp"

using namespace GameEngine;
class Actor;

class World : public std::enable_shared_from_this<World>
{
public:

	template<typename T> std::shared_ptr<T> CreateActor(Transform Transform = Transform())
	{
		static_assert(std::is_base_of<Actor, T>::value,
			"T must be derived from Actor");
		std::shared_ptr<T> NewActor = std::make_shared<T>(shared_from_this());
		RegisterActor(NewActor);
		NewActor->ActorTransform = Transform;
		return NewActor;
	}

	void Tick(float DeltaTime);
	void RenderAllRegisteredActors();

protected:

	std::vector<std::shared_ptr<Actor>> RegisteredActors;

	void RegisterActor(std::shared_ptr<Actor> NewActor);
	void TickAllRegisteredActors(float DeltaTime);
};