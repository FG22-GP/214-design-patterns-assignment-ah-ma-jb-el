#pragma once

#include "Core.hpp"
#include "Engine/World/World.hpp"
#include "Data/Transform.hpp"

namespace GameEngine
{
	class ActorComponent;

	class Actor
	{

	public:
		virtual void Tick(float DeltaTime);

		//Do not call this manually, instead use the CreateActor() function in the World
		Actor(std::shared_ptr<World> ParentWorld, Transform StartTransform);

		GAME_API std::shared_ptr<World> GetWorld() { return ParentWorld; }

		// Creates an ActorComponentT of type T and adds it to the Actor's component list.
		// Returns the newly created ActorComponentT
		template<typename T> GAME_API std::shared_ptr<T> AddComponent();
		GAME_API bool TryRemoveComponent(std::shared_ptr<ActorComponent> Comp);
		template<typename T> GAME_API bool TryRemoveComponent();

		GAME_API std::vector<std::shared_ptr<ActorComponent>> GetComponents() { return ChildComponents; }

		Transform ActorTransform;

	protected:

		std::shared_ptr<World> ParentWorld;
		std::vector<std::shared_ptr<ActorComponent>> ChildComponents;

	};
}