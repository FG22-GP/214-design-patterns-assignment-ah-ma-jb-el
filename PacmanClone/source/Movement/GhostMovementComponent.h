#pragma once

#include "PacmanCore.h"

#include "MovementComponent.h"
#include "World\Actors\ActorComponent.hpp"
#include "Data/Vectors/Vector2.hpp"
#include "Event/Event.h"

class GridLink;
class GridCell;

class GhostMovementComponent : public MovementComponent
{
public:
    GhostMovementComponent(std::shared_ptr<Actor> ParentActor) :
        MovementComponent(ParentActor)
    {
    }

};
