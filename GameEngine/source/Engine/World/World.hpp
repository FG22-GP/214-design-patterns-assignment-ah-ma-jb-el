#pragma once

#include "Core.hpp"

class Actor;

class World : public std::enable_shared_from_this<World>
{
public:

	std::shared_ptr<Actor> CreateActor();

protected:

	std::vector<std::shared_ptr<Actor>> RegisteredActors;

	void RegisterActor(std::shared_ptr<Actor> NewActor);
	void TickAllRegisteredActors(float DeltaTime);
};

