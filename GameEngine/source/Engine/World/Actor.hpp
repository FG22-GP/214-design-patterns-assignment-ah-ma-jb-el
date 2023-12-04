#pragma once

#include "Core.hpp"
#include "World.hpp"

class Actor
{
public:
	virtual void Tick(float DeltaTime) {}

	Actor(std::shared_ptr<World> ParentWorld);

	std::shared_ptr<World> ParentWorld;

};

