#pragma once
#include "IGhost.h"
#include "World/Actors/Actor.hpp"

class Ghost_Magnus : public Actor, public IGhost
{
public:
    void ChasePlayer() override;
    
};
