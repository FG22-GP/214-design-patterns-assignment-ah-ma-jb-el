#pragma once

#include "Core.hpp"

namespace GameEngine
{
	class Actor;

	class ActorComponent
	{
	public:
		virtual void Tick(float DeltaTime) {}

		ActorComponent(std::shared_ptr<Actor> ParentActor)
		{
			this->Parent = ParentActor;
		}

		GAME_API std::shared_ptr<Actor> GetParent() { return Parent; }

	protected:
		std::shared_ptr<Actor> Parent;
	};

}

