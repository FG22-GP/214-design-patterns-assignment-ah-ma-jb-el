#pragma once

#include "Core.hpp"

class Actor;

class ActorComponent
{
public:
	virtual void Tick(float DeltaTime) {}

	ActorComponent(std::shared_ptr<Actor> ParentActor)
	{
		this->Parent = ParentActor;
	}

protected:
	std::shared_ptr<Actor> Parent;
};

