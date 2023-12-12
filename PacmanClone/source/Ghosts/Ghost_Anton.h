#pragma once
#include "IGhost.h"
#include "World/Actors/Actor.hpp"

class Ghost_Anton : public IGhost
{
public:
    Ghost_Anton(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform);
protected:
    Point2 GetTargetCoord() override;
};
