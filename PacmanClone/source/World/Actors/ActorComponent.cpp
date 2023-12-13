#include "PacmanCore.h"
#include "ActorComponent.hpp"
#include "Actor.hpp"

ActorComponent::ActorComponent(std::shared_ptr<Actor> ParentActor)
{
	this->Parent = ParentActor;
}