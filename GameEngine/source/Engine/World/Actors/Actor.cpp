#include "Core.hpp"
#include "Actor.hpp"
#include "ActorComponent.hpp"
#include "Data/Transform.hpp"

namespace GameEngine
{
	void Actor::Tick(float DeltaTime)
	{
		for (std::shared_ptr<ActorComponent> Child : ChildComponents)
		{
			Child->Tick(DeltaTime);
		}
	}

	Actor::Actor(std::shared_ptr<World> ParentWorld, Transform StartTransform)
	{
		this->ParentWorld = ParentWorld;
		this->ActorTransform = StartTransform;
	}

	bool Actor::TryRemoveComponentRef(std::shared_ptr<ActorComponent> Comp)
	{
		for (size_t i = 0; i < ChildComponents.size(); i++)
		{
			if (Comp != ChildComponents[i]) continue;

			ChildComponents.erase(ChildComponents.begin() + i);
			Comp->OnDestroy();
			return true;
		}
		return false;
	}
	
}