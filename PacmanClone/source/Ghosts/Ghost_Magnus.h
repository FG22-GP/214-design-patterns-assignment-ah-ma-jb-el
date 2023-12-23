#pragma once
#include "IGhost.h"
#include "World/Actors/Actor.hpp"

class Ghost_Magnus : public IGhost
{
public:
    Ghost_Magnus(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform);
protected:
    Point2 GetTargetCoord() override;
};
