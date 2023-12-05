#pragma once

#include "Core.hpp"

namespace GameEngine
{
	class Actor;

	class ActorComponent
	{
	public:
		virtual void Tick(float DeltaTime) {}
		virtual void OnStart() {}
		virtual void OnDestroy() {}

		ActorComponent(std::shared_ptr<Actor> ParentActor);
		~ActorComponent();

		GAME_API std::shared_ptr<Actor> GetParent() { return Parent; }

	protected:
		std::shared_ptr<Actor> Parent;
	};

}

