#pragma once
#include "IGhost.h"
#include "World/Actors/Actor.hpp"

class Ghost_Anton : public IGhost
{
protected:
    Point2 GetTargetCoord() override;
};
