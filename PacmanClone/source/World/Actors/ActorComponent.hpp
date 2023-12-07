#pragma once

#include "PacmanCore.h"

class Actor;

class ActorComponent
{
public:
	virtual void Tick(float DeltaTime) {}
	virtual void OnStart() {}
	virtual void OnDestroy() {}

	ActorComponent(std::shared_ptr<Actor> ParentActor);
	~ActorComponent();

	std::shared_ptr<Actor> GetParent() { return Parent; }

protected:
	std::shared_ptr<Actor> Parent;
};