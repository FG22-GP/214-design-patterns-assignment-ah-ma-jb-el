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

	bool Actor::TryRemoveComponent(std::shared_ptr<ActorComponent> Comp)
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


	template<typename T> std::shared_ptr<T> Actor::AddComponent()
	{
		static_assert(std::is_base_of<ActorComponent, T>::value,
			"T must be derived from ActorComponent");
		std::shared_ptr<T> NewComp = std::make_shared<T>();
		ChildComponents.push_back(NewComp);
		NewComp->OnStart();
		return NewComp;
	}

	template<typename T>
	bool Actor::TryRemoveComponent()
	{
		static_assert(std::is_base_of<ActorComponent, T>::value,
			"T must be derived from ActorComponent");
		for (size_t i = 0; i < ChildComponents.size(); i++)
		{
			if (dynamic_cast<T*>(ChildComponents[i]) != nullptr)
			{
				ChildComponents[i]->OnDestroy();
				ChildComponents.erase(ChildComponents.begin() + i);
				return true;
			}
			
		}
		return false;
	}
}