#include "Core.hpp"
#include "ActorComponent.hpp"
#include "Actor.hpp"

namespace GameEngine
{
	ActorComponent::ActorComponent(std::shared_ptr<Actor> ParentActor)
	{
		this->Parent = ParentActor;
	}

	ActorComponent::~ActorComponent()
	{
		if (Parent != nullptr && 
			Parent->TryRemoveComponentRef(std::shared_ptr<ActorComponent>(this)))
		{
			//TryRemoveComponent() calls OnDestroy() if it succeeds
		}
		else
		{
			OnDestroy();
		}
	}

}
