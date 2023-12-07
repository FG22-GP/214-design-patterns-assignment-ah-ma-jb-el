#pragma once

#include "Core.hpp"
#include "World\World.hpp"
#include "Data/Transform.hpp"
#include "ActorComponent.hpp"
#include "SpriteComponent.hpp"


class Actor
{

public:
	virtual void Tick(float DeltaTime);

	//Do not call this manually, instead use the CreateActor() function in the World
	Actor(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform);

	std::shared_ptr<World> GetWorld() { return ParentWorld; }

	// Creates an ActorComponentT of type T and adds it to the Actor's component list.
	// Returns the newly created ActorComponentT
	template<typename T> std::shared_ptr<T> AddComponent();
	bool TryRemoveComponentRef(std::shared_ptr<ActorComponent> Comp);
	template<typename T> bool TryRemoveComponent();

	std::vector<std::shared_ptr<ActorComponent>> GetComponents() { return ChildComponents; }

	GameEngine::Transform ActorTransform;

protected:

	std::shared_ptr<World> ParentWorld;
	std::vector<std::shared_ptr<ActorComponent>> ChildComponents;

};

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