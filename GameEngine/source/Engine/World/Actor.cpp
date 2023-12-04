#include "Core.hpp"
#include "Actor.hpp"


Actor::Actor(std::shared_ptr<World> ParentWorld)
{
	this->ParentWorld = ParentWorld;
}
