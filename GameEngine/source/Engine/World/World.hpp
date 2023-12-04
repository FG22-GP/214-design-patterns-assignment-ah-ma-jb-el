#pragma once

#include "Core.hpp"

class Actor;

class World : public std::enable_shared_from_this<World>
{
public:

	void RegisterActor(std::shared_ptr<Actor> NewActor);

	std::shared_ptr<Actor> CreateActor();

protected:

	std::vector<std::shared_ptr<Actor>> RegisteredActors;

	void TickAllRegisteredActors(float DeltaTime);
};

