#pragma once

#include "PacmanCore.h"
#include "Data\Transform.hpp"

using namespace GameEngine;
class Actor;

class World
{
public:

	template<typename T> std::shared_ptr<T> CreateActor(Transform Transform = Transform());

	void Tick(float DeltaTime);
	void RenderAllRegisteredActors();

	bool bShouldTickActors = true;

protected:

	std::vector<std::shared_ptr<Actor>> RegisteredActors;

	void RegisterActor(std::shared_ptr<Actor> NewActor);
	void TickAllRegisteredActors(float DeltaTime);
};

template<typename T>
inline std::shared_ptr<T> World::CreateActor(Transform Transform)
{
	static_assert(std::is_base_of<Actor, T>::value,
		"T must be derived from Actor");
	std::shared_ptr<T> NewActor = std::make_shared<T>(std::shared_ptr<World>(this), Transform);
	RegisterActor(NewActor);
	NewActor->ActorTransform = Transform;
	return NewActor;
}
