#pragma once
#include "IGhost.h"
#include "World/Actors/Actor.hpp"

class Ghost_Anton : public IGhost
{
public:
    void ChasePlayer() override;
    
};
