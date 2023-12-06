#pragma once

#include "Core.hpp"
namespace GameEngine
{
	class Actor;
	struct Transform;

	class World : public std::enable_shared_from_this<World>
	{
	public:

		template<typename T> GAME_API std::shared_ptr<T> CreateActor();
		template<typename T> GAME_API std::shared_ptr<T> CreateActor(Transform Transform);

		void Tick(float DeltaTime);
		void RenderAllRegisteredActors();

	protected:

		std::vector<std::shared_ptr<Actor>> RegisteredActors;

		void RegisterActor(std::shared_ptr<Actor> NewActor);
		void TickAllRegisteredActors(float DeltaTime);
	};
}


