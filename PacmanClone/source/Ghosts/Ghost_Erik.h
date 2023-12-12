#pragma once
#include "IGhost.h"
#include "World/Actors/Actor.hpp"

class Ghost_Erik : public IGhost
{
protected:
    Point2 GetTargetCoord() override;
    
};
