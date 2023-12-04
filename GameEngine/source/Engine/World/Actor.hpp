#pragma once

#include "Core.hpp"
#include "World.hpp"

class ActorComponent;

class Actor
{
public:
	virtual void Tick(float DeltaTime);

	//Do not call this manually, instead use the CreateActor() function in the World
	Actor(std::shared_ptr<World> ParentWorld);

	std::shared_ptr<World> GetWorld() { return ParentWorld; }

	// Creates an ActorComponentT of type T and adds it to the Actor's component list.
	// Returns the newly created ActorComponentT
	template<typename T> std::shared_ptr<T> AddComponent();

	std::vector<std::shared_ptr<ActorComponent>> GetChildren() { return ChildComponents; }

protected:

	std::shared_ptr<World> ParentWorld;
	std::vector<std::shared_ptr<ActorComponent>> ChildComponents;

};