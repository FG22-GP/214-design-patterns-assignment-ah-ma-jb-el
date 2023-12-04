#pragma once

#include "Core.hpp"

class Actor;

class World : public std::enable_shared_from_this<World>
{
public:

	template<typename T> std::shared_ptr<T> CreateActor();

protected:

	std::vector<std::shared_ptr<Actor>> RegisteredActors;

	void RegisterActor(std::shared_ptr<Actor> NewActor);
	void TickAllRegisteredActors(float DeltaTime);
};

