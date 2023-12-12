#pragma once
#include "IGhost.h"
#include "World/Actors/Actor.hpp"

class Ghost_Erik : public IGhost
{
public:
    Ghost_Erik(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform);
protected:
    Point2 GetTargetCoord() override;
    
};
