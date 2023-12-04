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


	template<typename T> std::shared_ptr<T> Actor::AddComponent()
	{
		static_assert(std::is_base_of<ActorComponent, T>::value,
			"T must be derived from ActorComponent");
		std::shared_ptr<T> NewComp = std::make_shared<T>();
		ChildComponents.push_back(NewComp);
		return NewComp;
	}
}