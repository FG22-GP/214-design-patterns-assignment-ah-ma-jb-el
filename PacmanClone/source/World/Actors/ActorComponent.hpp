#pragma once

#include "PacmanCore.h"

class Actor;

class ActorComponent
{
public:
	virtual ~ActorComponent() = default;
	virtual void Tick(float DeltaTime) {}
	virtual void OnStart() {}
	virtual void OnDestroy() {}

	ActorComponent(std::shared_ptr<Actor> ParentActor);

	std::shared_ptr<Actor> GetParent() { return Parent; }
	bool bIsEnabled();

protected:
	std::shared_ptr<Actor> Parent;
};