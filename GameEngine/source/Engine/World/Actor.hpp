#pragma once

#include "Core.hpp"
#include "World.hpp"

class Actor
{
public:
	virtual void Tick(float DeltaTime) {}

	//Do not call this manually, instead use the CreateActor() function in the World
	Actor(std::shared_ptr<World> ParentWorld);

	std::shared_ptr<World> GetWorld() { return ParentWorld; }

protected:

	std::shared_ptr<World> ParentWorld;

};

