#pragma once
#include "IGhost.h"
#include "World/Actors/Actor.hpp"

class Ghost_Anton;

class Ghost_Johan : public IGhost
{
public:
    Ghost_Johan(std::shared_ptr<World> ParentWorld, GameEngine::Transform StartTransform);

    void GiveFriend(const std::shared_ptr<Ghost_Anton>& friendly);
protected:
    Point2 GetTargetCoord() override;

private:
    std::shared_ptr<Ghost_Anton> Friend;
};
